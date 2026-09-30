
#include "Audio.h"
#include "Audio_LoadWave_Command.h"
#include "Audio_AsyncLoadWave_Command.h"
#include "SoundManager.h"
#include "Internal_FileCB_Command.h"
#include "QueueMan.h"
#include "WaveMan.h"
#include "Audio_RemoveAllWaves_Command.h"

Audio* Audio::pInstance = nullptr;

Audio::Audio()
{
	this->pWaveTable = new WaveTable();
}

Audio::~Audio()
{
	delete this->pWaveTable;
}

void Audio::Destroy()
{
	delete Audio::pInstance;
	Audio::pInstance = nullptr;
}

void Audio::Create()
{
	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new Audio();
	}

}

void Audio::WaveTableDump()
{
	Audio* pAudio = Audio::GetInstance();
	pAudio->pWaveTable->Dump();
}

void Audio::RemoveAllWaves()
{
	bool doneFlag = false;
	Internal_FileCB_Command* pCBCommand = new Internal_FileCB_Command(doneFlag);
	Audio_RemoveAllWaves_Command* pCommand = new Audio_RemoveAllWaves_Command(pCBCommand);

	Debug::out("-->Audio_RemoveAll_Command\n");
	QueueMan::SendAudio(pCommand);
	while (!doneFlag);
}

void Audio::Load(Async, Wave::ID wave_id, const char* const pWaveName, UserAsyncLoadCallBack* pUserAsyncLoadCallback)
{
	Audio* pAudio = Audio::GetInstance();

	//Is Wave in the WaveTable?
	WaveTable* pWaveTable = pAudio->pWaveTable;
	assert(pWaveTable);
	WaveTable::Table* pTable = pWaveTable->Find(wave_id);

	// Not there...
	if (pTable == nullptr)
	{
		pWaveTable->Register(wave_id, Wave::Status::PENDING);

		assert(pWaveName);

		// Setup the Callback
		pUserAsyncLoadCallback->Set(wave_id, pWaveName);

		Audio_AsyncLoadWave_Command* pCommand = new Audio_AsyncLoadWave_Command(wave_id, pWaveName, pUserAsyncLoadCallback);

		//   Debug::out("--> Audio_LoadAsyncWave_Cmd \n");
		QueueMan::SendAudio(pCommand);

	}
	else
	{
		// its Ready or Pending...
		if (pTable->status == Wave::Status::READY || pTable->status == Wave::Status::PENDING)
		{
			// Do nothing... 
		}
		else
		{
			// bad...
			assert(false);
		}
	}
}

void Audio::Load(Blocking, Wave::ID wave_id, const char* const pWaveName)
{
	Audio* pAudio = Audio::GetInstance();

	//Is Wave in the WaveTable?
	WaveTable* pWaveTable = pAudio->pWaveTable;
	assert(pWaveTable);
	WaveTable::Table* pTable = pWaveTable->Find(wave_id);

	// Not there...
	if (pTable == nullptr)
	{
		pWaveTable->Register(wave_id, Wave::Status::PENDING);

		assert(pWaveName);

		// Setup the Callback
		bool DoneFlag = false;
		Internal_FileCB_Command* pFileCB = new Internal_FileCB_Command(DoneFlag);

		Audio_LoadWave_Command* pCmd = new Audio_LoadWave_Command(wave_id, pWaveName, pFileCB);
		assert(pCmd);

		QueueMan::SendAudio(pCmd);


		// Block and spin until Callback
		while (!DoneFlag);

		Debug::out("Loaded File %s\n", pWaveName);

	}
	else
	{
		// its Ready or Pending...
		if (pTable->status == Wave::Status::READY || pTable->status == Wave::Status::PENDING)
		{
			// Do nothing... 
		}
		else
		{
			// bad...
			assert(false);
		}
	}
}

Audio* Audio::GetInstance()
{
	return pInstance;
}

WaveTable* Audio::GetWaveTable()
{
	Audio* pAudio = Audio::GetInstance();
	return pAudio->pWaveTable;
}
