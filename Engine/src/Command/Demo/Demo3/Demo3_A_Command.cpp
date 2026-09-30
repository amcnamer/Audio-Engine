//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo3_A_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"


Demo3_A_Command::Demo3_A_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo3_A_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	Trace::out("\n");
	Debug::out("--- Demo3 A: %dms --- \n", ms);
	Trace::out("\n");

	// Timer: 0 seconds
	//    Snd_A = Play 301 with priority : 10 vol : 10 %
	//    Snd_B = Play 301 with priority : 50 vol : 10 %
	//    Snd_C = Play 301 with priority : 150 vol : 10 %
	//    Print the status of the active sound call table

	// ---------------------------------------
	// Play A
	// ---------------------------------------

	Sound* pSndA = SoundManager::Add(Sound::ID::Coma, 10);
	assert(pSndA);

	// Vol & Pan
	assert(pSndA->SetVolume(0.10f) == Handle::Status::SUCCESS);
	assert(pSndA->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndA->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Play B
	// ---------------------------------------

	Sound* pSndB = SoundManager::Add(Sound::ID::Coma, 50);
	assert(pSndB);

	// Vol & Pan
	assert(pSndB->SetVolume(0.10f) == Handle::Status::SUCCESS);
	assert(pSndB->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndB->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Play C
	// ---------------------------------------

	Sound* pSndC = SoundManager::Add(Sound::ID::Coma, 150);
	assert(pSndC);

	// Vol & Pan
	assert(pSndC->SetVolume(0.10f) == Handle::Status::SUCCESS);
	assert(pSndC->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndC->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();
}

// --- End of File ---
