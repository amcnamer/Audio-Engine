

#include "Demo1_A_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"
#include "Audio.h"
#include "VoiceCallBack.h"

#include "PlaylistJukeBox.h"
#include "VoiceCallBack_One.h"
#include "Playlist_OneVoice_Command.h"



#include "Demo1_B_Command.h"
#include "Demo1_B1_Command.h"
#include "Demo1_B2_Command.h"

#include "Demo1_C_Command.h"
#include "Demo1_C1_Command.h"

#include "Demo1_D_Command.h"
#include "Demo1_D1_Command.h"

#include "Demo1_E_Command.h"
#include "Demo1_E1_Command.h"
#include "Demo1_E2_Command.h"
#include "Demo1_E3_Command.h"
#include "Demo1_E4_Command.h"

#include "Demo1_F_Command.h"
#include "Demo1_F1_Command.h"
#include "Demo1_F2_Command.h"
#include "Demo1_F3_Command.h"
#include "Demo1_KillCommand.h"


void Demo1_A_Command::Execute()
{
	Trace::out("\n");
	Trace::out("--- DEMO 1: Load() ----\n");
	Trace::out("\n");

	TimerEventMan::Reset();
	Azul::AnimTime start = TimerEventMan::GetTimeCurrent();

	// Load the waves
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Fiddle, "Fiddle_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Bassoon, "Bassoon_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Oboe, "Oboe3_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::SongA, "SongA.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::SongB, "SongB.wav");

	// Create the Playlist

	// 1 voice - playlist
	{
		VoiceCallBack* pVoiceCallback = new VoiceCallBack_One();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::Fiddle, pPlaylistCmd, pVoiceCallback, Wave::ID::Fiddle);
	}

	{
		VoiceCallBack* pVoiceCallback = new VoiceCallBack_One();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::Bassoon, pPlaylistCmd, pVoiceCallback, Wave::ID::Bassoon);
	}
	{
		VoiceCallBack* pVoiceCallback = new VoiceCallBack_One();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::Oboe, pPlaylistCmd, pVoiceCallback, Wave::ID::Oboe);
	}
	{
		VoiceCallBack* pVoiceCallback = new VoiceCallBack_One();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::SongA, pPlaylistCmd, pVoiceCallback, Wave::ID::SongA);
	}
	{
		VoiceCallBack* pVoiceCallback = new VoiceCallBack_One();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::SongB, pPlaylistCmd, pVoiceCallback, Wave::ID::SongB);
	}

	// How long did the load take?
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - start;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));
	Debug::out("Total Load Time: %d ms \n", ms);

	////spin til completed

// Set the start time...
	Command* pCmd;
	TimerEventMan::Reset();
	Azul::AnimTime* pDemoTime = new Azul::AnimTime();

	pCmd = new Demo1_B_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 0 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo1_B1_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 3 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo1_B2_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 6 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));



	pCmd = new Demo1_C_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 10 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo1_C1_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 15 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));



	pCmd = new Demo1_D_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 20 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo1_D1_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 25 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));



	pCmd = new Demo1_E_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 30 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo1_E1_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 35 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo1_E2_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 38 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo1_E3_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 60 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo1_E4_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 72 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));


	pCmd = new Demo1_F_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 80000 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	pCmd = new Demo1_F1_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 80500 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	pCmd = new Demo1_F2_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 81000 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	pCmd = new Demo1_F3_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 81500 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	pCmd = new Demo1_KillCommand(pDemoTime);
	TimerEventMan::Add(pCmd, 90 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));
}

