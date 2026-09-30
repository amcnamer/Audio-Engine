//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Audio_AsyncFileLoadCompleted_Command.h"
#include "File.h"

Audio_AsyncFileLoadCompleted_Command::Audio_AsyncFileLoadCompleted_Command(const char* const pWaveName, Wave* _pWave)
	: poWfx(nullptr),
	poRawBuff(nullptr),
	rawBuffSize(0),
	pWave(_pWave)
{
	assert(pWave);
	this->LoadBuffer(pWaveName);
}

void Audio_AsyncFileLoadCompleted_Command::Execute()
{
	Debug::out("Audio_AsyncFileLoadCompleted_Cmd::Execute()\n");

	assert(this->pWave);
	this->pWave->AsyncRegister(poWfx, poRawBuff, rawBuffSize);

	delete this;
}

void Audio_AsyncFileLoadCompleted_Command::LoadBuffer(const char* const pWaveName)
{
	assert(pWaveName);

	//Debug::out("Audio_AsyncFileLoadCompleted_Cmd::LoadBuffer(%s) start\n", pWaveName);

	//--------------------------------------------------------
	// zero out wfx and the buffer
	//--------------------------------------------------------

	this->poWfx = new WAVEFORMATEXTENSIBLE();
	assert(this->poWfx);

	*this->poWfx = { {0} };    // zeros out the complete structure

	// -------------------------------------------------------
	// Open File
	// -------------------------------------------------------

	File::Handle FileHandle;
	File::Error ferror;

	// Open file
	ferror = File::Open(FileHandle, pWaveName, File::Mode::READ, true);
	assert(ferror == File::Error::SUCCESS);

	// Set file to beginning
	ferror = File::Seek(FileHandle, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	// -------------------------------------------------------
	// Find and load specific Chunks
	// -------------------------------------------------------

	DWORD dwChunkPosition;
	DWORD filetype;
	ChunkError cerror;

	// Scan to the RIFF and load file type
	cerror = FindChunk(FileHandle, fourccRIFF, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);
	cerror = ReadChunkData(FileHandle, &filetype, sizeof(DWORD), dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	// Make sure its not in the compressed format, WAVE format is uncompressed
	if (filetype != fourccWAVE)
	{
		assert(false);
	}

	// Read the FMT: format
	cerror = FindChunk(FileHandle, fourccFMT, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);
	cerror = ReadChunkData(FileHandle, this->poWfx, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	// Scan to the DATA chunk, read the size, allocate buffer of that size
	cerror = FindChunk(FileHandle, fourccDATA, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	this->poRawBuff = new unsigned char[this->rawBuffSize];
	assert(this->poRawBuff);

	// Fill the data...
	cerror = ReadChunkData(FileHandle, this->poRawBuff, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	ferror = File::Close(FileHandle);
	assert(ferror == File::Error::SUCCESS);

	Debug::out("Audio_AsyncFileLoadCompleted_Cmd::LoadBuffer(%s) end\n", pWaveName);
}

//---  End of File ---
