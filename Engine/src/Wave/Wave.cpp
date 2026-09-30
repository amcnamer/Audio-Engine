
#include "XAudio2Wrapper.h"
#include "AudioEngine.h"
#include "Wave.h"
#include "StringEnum.h"
#include "Audio.h"
#include "Aux_FileCB_Command.h"
#include "QueueMan.h"
#include "UserAsyncLoadCallBack.h"
#include "Game_TransferAsyncLoadUserCallBack_Command.h"

Wave::Wave()
	: poWfx(nullptr),
	poRawBuff(nullptr),
	rawBuffSize(0),
	id(Wave::ID::Empty),
	strName("empty"),
	pIFileCB(nullptr),
	pUserAsyncLoadCallback(nullptr),
	status(Status::EMPTY),
	handle()
{

}

Wave::~Wave()
{
	delete this->poWfx;
	delete[] this->poRawBuff;
}

void Wave::SetId(Wave::ID _id)
{
	this->id = _id;
}
Wave::ID Wave::GetId() const
{
	return this->id;
}

void Wave::SetPending(const char* const pWaveName, Wave::ID wave_id, Internal_FileCB_Command* pFileCommand)
{
	this->id = wave_id;
	this->SetName(pWaveName);
	this->pIFileCB = pFileCommand;
	this->pUserAsyncLoadCallback = nullptr;
	this->status = Wave::Status::PENDING;
}

void Wave::SetPending(const char* const pWaveName, Wave::ID wave_id, UserAsyncLoadCallBack* pFileCommand)
{
	this->id = wave_id;
	this->SetName(pWaveName);
	this->pUserAsyncLoadCallback = pFileCommand;
	this->pIFileCB = nullptr;
	this->status = Wave::Status::PENDING;
}

void Wave::Dump()
{
	// Dump - Print contents to the debug output window
	Trace::out("\t\tWave(%p) %s \"%s\" \n", this, StringMe(this->id), this->strName);
}

void Wave::Clear()
{
	delete this->poWfx;
	this->poWfx = nullptr;

	delete[] this->poRawBuff;
	this->poRawBuff = nullptr;

	this->rawBuffSize = 0;

	this->id = Wave::ID::Empty;

	const char* pWaveName = "Empty";
	this->SetName(pWaveName);

	this->pIFileCB = nullptr;
	this->status = Status::EMPTY;
}

void Wave::Wash()
{
	DLink::Clear();
	this->Clear();
}

bool Wave::Compare(DLink* pTarget)
{
	Wave* pDataB = (Wave*)pTarget;
	bool _status = false;
	if (this->id == pDataB->id)
	{
		_status = true;
	}
	return _status;
}

void Wave::SetName(const char* const pWaveName)
{
	memset(this->strName, 0x0, Wave::NAME_SIZE);
	unsigned int len = strlen(pWaveName);
	const char* pEnd = pWaveName + len;
	const char* pStart = pEnd;

	while (pStart != pWaveName)
	{
		if (*pStart == '/')
		{
			pStart++;
			break;
		}
		pStart--;
	}
	strcpy_s(this->strName, Wave::NAME_SIZE, pStart);
}

void Wave::Register(WAVEFORMATEXTENSIBLE* _poWfx, RawData* _pRawDataBuff, unsigned long _rawBuffSize)
{
	this->poWfx = _poWfx;
	this->poRawBuff = _pRawDataBuff;
	this->rawBuffSize = _rawBuffSize;
	this->status = Wave::Status::READY;
	WaveTable* pWaveTable = Audio::GetWaveTable();
	assert(pWaveTable);
	pWaveTable->Update(this->id, Wave::Status::READY);
	Aux_FileCB_Command* pCommand = new Aux_FileCB_Command(this->pIFileCB);
	QueueMan::SendAux(pCommand);
}

void Wave::AsyncRegister(WAVEFORMATEXTENSIBLE* _poWfx, RawData* _pRawDataBuff, unsigned long _rawBuffSize)
{
	this->poWfx = _poWfx;
	this->poRawBuff = _pRawDataBuff;
	this->rawBuffSize = _rawBuffSize;
	this->status = Wave::Status::READY;
	WaveTable* pWaveTable = Audio::GetWaveTable();
	assert(pWaveTable);
	pWaveTable->Update(this->id, Wave::Status::READY);
	Game_TransferAsyncLoadUserCallBack_Command* pCommand = new Game_TransferAsyncLoadUserCallBack_Command(this->pUserAsyncLoadCallback);
	QueueMan::SendGame(pCommand);
}

void Wave::LoadBuffer(const char* const pWaveName)
{
	assert(pWaveName);

	//--------------------------------------------------------
	// zero out wfx and the buffer
	//--------------------------------------------------------

	this->poWfx = new WAVEFORMATEXTENSIBLE();
	assert(this->poWfx);

	*this->poWfx = { { 0 } };    // zeros out the complete structure

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
	ChunkError cError;

	// Scan to the RIFF and load file type
	cError = FindChunk(FileHandle, fourccRIFF, this->rawBuffSize, dwChunkPosition);
	assert(cError == ChunkError::CHUNK_SUCCESS);
	cError = ReadChunkData(FileHandle, &filetype, sizeof(DWORD), dwChunkPosition);
	assert(cError == ChunkError::CHUNK_SUCCESS);

	// Make sure its not in the compressed format, WAVE format is uncompressed
	if (filetype != fourccWAVE)
	{
		assert(false);
	}

	// Read the FMT: format
	cError = FindChunk(FileHandle, fourccFMT, this->rawBuffSize, dwChunkPosition);
	assert(cError == ChunkError::CHUNK_SUCCESS);
	cError = ReadChunkData(FileHandle, this->poWfx, this->rawBuffSize, dwChunkPosition);
	assert(cError == ChunkError::CHUNK_SUCCESS);

	// Scan to the DATA chunk, read the size, allocate buffer of that size
	cError = FindChunk(FileHandle, fourccDATA, this->rawBuffSize, dwChunkPosition);
	assert(cError == ChunkError::CHUNK_SUCCESS);

	this->poRawBuff = new unsigned char[this->rawBuffSize];
	assert(this->poRawBuff);

	// Fill the data...
	cError = ReadChunkData(FileHandle, this->poRawBuff, this->rawBuffSize, dwChunkPosition);
	assert(cError == ChunkError::CHUNK_SUCCESS);

	ferror = File::Close(FileHandle);
	assert(ferror == File::Error::SUCCESS);
}
