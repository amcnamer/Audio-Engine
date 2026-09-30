//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TimerEventMan.h"
#include "Audio.h"
#include "PlaylistJukeBox.h"
#include "TimerMan.h"

#include "Demo3.h"
#include "Demo3_A_Command.h"
#include "Demo3_D_Command.h"
#include "Demo3_E_Command.h"
#include "Demo3_F_Command.h"
#include "Demo3_G_Command.h"
#include "Demo3_H_Command.h"
#include "Demo3_I_Command.h"
#include "Demo3_J_Command.h"
#include "Demo3_K_Command.h"
#include "Demo3_Kill_Command.h"

#include "Playlist_OneVoice_Command.h"
#include "VoiceCallBack_One.h"


Demo3::Demo3(Azul::AnimTime time)
	: Demo(time)
{
	Trace::out("\n");
	Trace::out("******************************\n");
	Trace::out("**	   DEMO 3 - Priority    **\n");
	Trace::out("******************************\n");
}

Demo3::~Demo3()
{

}

void Demo3::Load()
{
	Trace::out("\n");
	Trace::out("--- DEMO 3: Load() ----\n");
	Trace::out("\n");

	TimerEventMan::Reset();
	Azul::AnimTime start = TimerEventMan::GetTimeCurrent();

	// Load the waves
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Coma, "Coma_mono.wav");

	// Create the Playlist
	{
		VoiceCallBack* pVoiceCallback = new VoiceCallBack_One();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::Coma, pPlaylistCmd, pVoiceCallback, Wave::ID::Coma);
	}

	// How long did the load take?
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - start;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));
	Debug::out("Total Load Time: %d ms \n", ms);
}

void Demo3::Execute()
{
	Trace::out("\n");
	Trace::out("--- DEMO 3: Execute() ----\n");

	// Set the start time...
	TimerEventMan::Reset();

	Azul::AnimTime* pDemoTime = new Azul::AnimTime();
	Command* pCmd;

	pCmd = new Demo3_A_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 0 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo3_D_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 1 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo3_E_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 2 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo3_F_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 3 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo3_G_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 4 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo3_H_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 5 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo3_I_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 6 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo3_J_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 7 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo3_K_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 8 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo3_Kill_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 13 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

}

// --- End of File ---