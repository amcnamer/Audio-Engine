//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo2_KillCommand.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"
#include "WaveMan.h"
#include "Audio.h"


Demo2_KillCommand::Demo2_KillCommand(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo2_KillCommand::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	// Its the last part of Demo2 so I can delete pStartTime
	delete this->pStartTime;


	// Timer: 60 seconds
	//    Stop SndC
	//    Initiated from Game side
	//       Unload(501 wave);
	//       Unload(502 wave);
	//       Unload(503 wave);
	//  Print the wave table

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::KillAllActive();
	Sound::PrintPriorityTable();

	// ---------------------------------------
	// Wave Table
	// ---------------------------------------
	Audio::WaveTableDump();
	Audio::RemoveAllWaves();
	Audio::WaveTableDump();

	Trace::out("\n");
	Debug::out("--- Demo2: Kill: %dms --- \n", ms);
	Trace::out("\n");
}

// --- End of File ---
