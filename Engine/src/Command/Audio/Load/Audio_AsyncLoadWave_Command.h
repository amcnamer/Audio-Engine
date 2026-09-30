

#ifndef AUDIO_ASYNC_LOAD_WAVE_COMMAND_H
#define AUDIO_ASYNC_LOAD_WAVE_COMMAND_H

#include "Command.h"
#include "Wave.h"
#include "UserAsyncLoadCallBack.h"

class Audio_AsyncLoadWave_Command : public Command
{
public:
	// Big 4
	Audio_AsyncLoadWave_Command() = delete;
	Audio_AsyncLoadWave_Command(const Audio_AsyncLoadWave_Command&) = delete;
	Audio_AsyncLoadWave_Command& operator = (const Audio_AsyncLoadWave_Command&) = delete;
	~Audio_AsyncLoadWave_Command() = default;

	Audio_AsyncLoadWave_Command(Wave::ID id, const char* const pWaveName, UserAsyncLoadCallBack* pUserAsyncLoadCallback);

	virtual void Execute() override;

public:
	// Data
	Wave::ID id;
	const char* const pWaveName;
	UserAsyncLoadCallBack* pUserAsyncLoadCallback;
};

#endif

// --- End of File ---
