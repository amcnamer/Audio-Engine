

#include "Audio_AsyncLoadWave_Command.h"
#include "WaveMan.h"

Audio_AsyncLoadWave_Command::Audio_AsyncLoadWave_Command(Wave::ID _id, const char* const _pWaveName, UserAsyncLoadCallBack* _pUserAsyncLoadCallback)
	: Command(),
	id(_id),
	pWaveName(_pWaveName),
	pUserAsyncLoadCallback(_pUserAsyncLoadCallback)
{
	assert(pWaveName);
	assert(pUserAsyncLoadCallback);
}

void Audio_AsyncLoadWave_Command::Execute()
{
	Debug::out("Audio_AsyncLoadWave_Command::Execute(%s)\n", this->pWaveName);

	WaveMan::Add(this->id, this->pWaveName, this->pUserAsyncLoadCallback);

	delete this;
}


// --- End of File ---
