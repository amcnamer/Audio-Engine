
#ifndef AUDIO_H
#define AUDIO_H

#include "Wave.h"
#include "WaveTable.h"

class UserAsyncLoadCallBack;

class Audio
{
public:
	enum class Blocking
	{
		LOAD
	};

	enum class Async
	{
		LOAD
	};

public:
	static void Create();
	static void Destroy();

	static void Load(const Blocking, Wave::ID wave_id, const char* const pWaveName);
	static void Load(const Async, Wave::ID wave_id, const char* const pWaveName, UserAsyncLoadCallBack *pUserCallback);

	static void RemoveAllWaves();

	static WaveTable* GetWaveTable();
	static void WaveTableDump();

private:
	Audio();
	Audio(const Audio&) = delete;
	Audio& operator = (const Audio&) = delete;
	~Audio();

	WaveTable* pWaveTable;

	static Audio* GetInstance();
	static Audio* pInstance;
};

#endif