
#include "TimerEventMan.h"
#include "Audio.h"
#include "PlaylistJukeBox.h"
#include "VoiceCallBack_Stitched.h"
#include "Playlist_OneVoice_Command.h"

#include "Demo2.h"
#include "Demo2_A_Command.h"
#include "Demo2_B_Command.h"
#include "Demo2_C_Command.h"
#include "Demo2_D_Command.h"
#include "Demo2_KillCommand.h"

Demo2::Demo2(Azul::AnimTime time)
	:Demo(time)
{
	Trace::out("\n");
	Trace::out("******************************\n");
	Trace::out("**DEMO 2 - Callback Stitching**\n");
	Trace::out("******************************\n");
}
Demo2::~Demo2()
{

}

void Demo2::Load()
{
	Trace::out("\n");
	Trace::out("--- DEMO 2: Load() ----\n");
	Trace::out("\n");

	TimerEventMan::Reset();
	Azul::AnimTime start = TimerEventMan::GetTimeCurrent();

	// Load the waves
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Intro, "Intro_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::A, "A_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::AtoB, "AtoB_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::B, "B_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::BtoC, "BtoC_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::C, "C_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::CtoA, "CtoA_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::End, "End_mono.wav");

	// Create the Playlist

	// 1 voice - stitched playlist
	{
		int count = 8;
		Wave::ID* pWaveList = new Wave::ID[8];
		pWaveList[0] = Wave::ID::Intro;
		pWaveList[1] = Wave::ID::A;
		pWaveList[2] = Wave::ID::AtoB;
		pWaveList[3] = Wave::ID::B;
		pWaveList[4] = Wave::ID::BtoC;
		pWaveList[5] = Wave::ID::C;
		pWaveList[6] = Wave::ID::CtoA;
		pWaveList[7] = Wave::ID::End;

		VoiceCallBack* pVoiceCallback = new VoiceCallBack_Stitched(pWaveList, count);
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::Intro, pPlaylistCmd, pVoiceCallback, Wave::ID::Intro);
	}

	// How long did the load take?
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - start;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));
	Debug::out("Total Load Time: %d ms \n", ms);
}

void Demo2::Execute()
{
	Trace::out("\n");
	Trace::out("--- DEMO 2: Execute() ----\n");

	// Set the start time...
	TimerEventMan::Reset();

	Azul::AnimTime* pDemoTime = new Azul::AnimTime();
	Command* pCmd;

	pCmd = new Demo2_A_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 0 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo2_B_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 10 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo2_C_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 20 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo2_D_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 30 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo2_B_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 40 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo2_C_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 50 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo2_KillCommand(pDemoTime);
	TimerEventMan::Add(pCmd, 53 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));
}
