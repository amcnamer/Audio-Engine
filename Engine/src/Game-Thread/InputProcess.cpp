//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "InputProcess.h"
#include "SoundManager.h"
#include "ASoundMan.h"
#include "TimerMan.h"
#include "Input.h"
#include "Audio.h"

#include "Demo1.h"
#include "Demo2.h"
#include "Demo3.h"
#include "Demo4.h"
#include "Demo5.h"

static bool Key_1_State = false;
static bool Key_2_State = false;
static bool Key_3_State = false;
static bool Key_4_State = false;
static bool Key_5_State = false;

static bool Key_T_State = false;
static bool Key_W_State = false;
static bool Key_M_State = false;

void InputProcess()
{
	// Hit the "1" key to start
	if (Input::GetKeyPress(KeyBoard::Key_1) && (Key_1_State == false))
	{
		// avoid a double throw of the key
		Key_1_State = true;

		Demo1 d(TimerMan::GetTimeCurrent());

		d.Load();
		d.Execute();
	}

	// Hit the "2" key to start
	if (Input::GetKeyPress(KeyBoard::Key_2) && (Key_2_State == false))
	{
		// avoid a double throw of the key
		Key_2_State = true;

		Demo2 d(TimerMan::GetTimeCurrent());

		d.Load();
		d.Execute();
	}

	// Hit the "3" key to start
	if (Input::GetKeyPress(KeyBoard::Key_3) && (Key_3_State == false))
	{
		// avoid a double throw of the key
		Key_3_State = true;

		Demo3 d(TimerMan::GetTimeCurrent());

		d.Load();
		d.Execute();
	}

	// Hit the "4" key to start
	if (Input::GetKeyPress(KeyBoard::Key_4) && (Key_4_State == false))
	{
		// avoid a double throw of the key
		Key_4_State = true;

		Demo4 d(TimerMan::GetTimeCurrent());

		d.Load();
		d.Execute();
	}

	// Hit the "5" key to start
	if (Input::GetKeyPress(KeyBoard::Key_5) && (Key_5_State == false))
	{
		// avoid a double throw of the key
		Key_5_State = true;

		Demo5 d(TimerMan::GetTimeCurrent());

		d.Load();
		d.Execute();
	}

	// Hit the "T" key to start
	if (Input::GetKeyPress(KeyBoard::Key_T) && (Key_T_State == false))
	{
		// avoid a double throw of the key
		Key_T_State = true;
		Sound::PrintPriorityTable();
	}

	if (!Input::GetKeyPress(KeyBoard::Key_T))
	{
		// avoid a double throw of the key
		Key_T_State = false;
	}

	// Hit the "M" key to start
	if (Input::GetKeyPress(KeyBoard::Key_M) && (Key_M_State == false))
	{
		// avoid a double throw of the key
		Key_M_State = true;
		Trace::out("\nASnd Man: ");
		ASoundMan::Dump();

		Trace::out("\nSnd Man:");
		SoundManager::Dump();
	}

	if (!Input::GetKeyPress(KeyBoard::Key_M))
	{
		// avoid a double throw of the key
		Key_M_State = false;
	}

	if (!Input::GetKeyPress(KeyBoard::Key_W))
	{
		// avoid a double throw of the key
		Key_W_State = false;
	}

	// Hit the "W" key to start
	if (Input::GetKeyPress(KeyBoard::Key_W) && (Key_W_State == false))
	{
		// avoid a double throw of the key
		Key_W_State = true;
		Audio::WaveTableDump();
	}
}


// --- End of File ---
