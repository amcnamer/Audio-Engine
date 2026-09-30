

#ifndef USER_ASYNC_LOAD_CALLBACK_H
#define USER_ASYNC_LOAD_CALLBACK_H

#include "Sound.h"
#include "ASound.h"
#include "Wave.h"
#include "TimerMan.h"

class UserAsyncLoadCallBack
{
public:
	UserAsyncLoadCallBack();
	UserAsyncLoadCallBack(const UserAsyncLoadCallBack&) = delete;
	UserAsyncLoadCallBack& operator = (const UserAsyncLoadCallBack&) = delete;
	~UserAsyncLoadCallBack() = default;

	void Execute();

	void Set(Wave::ID id, const char* _pWaveName);
	Wave::ID GetWaveID();

private:
	// Return data...
	char	 pWaveName[Wave::NAME_SIZE];
	Wave::ID wave_id;
	Azul::AnimTime    timeStart;
	Azul::AnimTime    timeEnd;
};

#endif

// --- End of File ---