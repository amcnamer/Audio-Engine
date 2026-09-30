//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo5_A_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"
#include "Audio.h"
#include "UserAsyncLoadCallback.h"


Demo5_A_Command::Demo5_A_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo5_A_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	Trace::out("\n");
	Debug::out("--- Demo5: Start %d ms ---\n", ms);
	Trace::out("\n");

	// Timer: 0 seconds
	//    SndA = Play 501, vol : 30 %, pan : 100 % Right, Priority default 
	//       Add Debug::out() to show the call on the correct thread
	//    Start wave loading async data with GameLoadingCallback()
	//       Game thread initiates the Beethoven wave data load
	//       The callback is created on game side
	//       Will be triggered when that wave data(Beethoven is loaded)
	//       Add Debug::out() to show the call on the correct thread
	//    SndB = Play 502, vol: 30 %, pan : 100 % left, Priority default 
	//       Add Debug::out() to show the call on the correct thread

	// ---------------------------------------
	// Play A
	// ---------------------------------------

	Sound* pSndA = SoundManager::Add(Sound::ID::Electro);
	assert(pSndA);

	// Vol & Pan
	assert(pSndA->SetVolume(0.30f) == Handle::Status::SUCCESS);
	assert(pSndA->Pan(1.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndA->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Async load Beethoven
	// ---------------------------------------

	UserAsyncLoadCallBack* pUserAsyncLoadCallBack = new UserAsyncLoadCallBack();
	Audio::Load(Audio::Async::LOAD, Wave::ID::Beethoven, "Beethoven_stereo.wav", pUserAsyncLoadCallBack);

	// ---------------------------------------
	// Play B
	// ---------------------------------------

	Sound* pSndB = SoundManager::Add(Sound::ID::Alert);
	assert(pSndB);

	// Vol & Pan
	assert(pSndB->SetVolume(0.30f) == Handle::Status::SUCCESS);
	assert(pSndB->Pan(-1.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndB->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();
	Audio::WaveTableDump();

}

// --- End of File ---
