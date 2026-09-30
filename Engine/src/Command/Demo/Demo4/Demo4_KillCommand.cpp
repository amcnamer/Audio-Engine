//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo4_KillCommand.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"
#include "WaveMan.h"
#include "Audio.h"

void Demo4_KillCommand::Execute()
{
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
	Debug::out("--- Demo4: Kill From Callback --- \n");
	Trace::out("\n");
}

// --- End of File ---
