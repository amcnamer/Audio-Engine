
//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Audio_FileLoadCompleted_Command.h"

Audio_FileLoadCompleted_Command::Audio_FileLoadCompleted_Command(const char* const pWaveName, Wave* _pWave)
	: pWfx(nullptr),
	pRawBuff(nullptr),
	rawBuffSize(0),
	pWave(_pWave)
{
	assert(pWave);
	this->LoadBuffer(pWaveName);
}

void Audio_FileLoadCompleted_Command::Execute()
{
	//Debug::out("Register Wave loaded");

	assert(this->pWave);
	this->pWave->Register(pWfx, pRawBuff, rawBuffSize);

	delete this;
}

void Audio_FileLoadCompleted_Command::LoadBuffer(const char* const pWaveName)
{
	assert(pWaveName);

	//	Debug::out("Audio_FileLoadCompleted_Cmd::LoadBuffer(%s) start\n", pWaveName);

		//--------------------------------------------------------
		// zero out wfx and the buffer
		//--------------------------------------------------------

	this->pWfx = new WAVEFORMATEXTENSIBLE();
	assert(this->pWfx);

	*this->pWfx = { {0} };    // zeros out the complete structure

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
	cerror = ReadChunkData(FileHandle, this->pWfx, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	// Scan to the DATA chunk, read the size, allocate buffer of that size
	cerror = FindChunk(FileHandle, fourccDATA, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	this->pRawBuff = new unsigned char[this->rawBuffSize];
	assert(this->pRawBuff);

	// Fill the data...
	cerror = ReadChunkData(FileHandle, this->pRawBuff, this->rawBuffSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	ferror = File::Close(FileHandle);
	assert(ferror == File::Error::SUCCESS);

	Debug::out("FileDataCommand::LoadBuffer(%s) end\n", pWaveName);
}
