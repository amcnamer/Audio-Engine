
#include "TimerEventMan.h"
#include "Audio.h"
#include "PlaylistJukeBox.h"
#include "VoiceCallBack_One.h"
#include "Playlist_OneVoice_Command.h"

#include "Demo5.h"
#include "Demo5_A_Command.h"
#include "Demo5_B_Command.h"
#include "Demo5_KillCommand.h"

Demo5::Demo5(Azul::AnimTime time)
	:Demo(time)
{
	Trace::out("\n");
	Trace::out("******************************\n");
	Trace::out("**      DEMO 5 - Async      **\n");
	Trace::out("******************************\n");
}
Demo5::~Demo5()
{

}

void Demo5::Load()
{
	Trace::out("\n");
	Trace::out("--- DEMO 5: Load() ----\n");
	Trace::out("\n");

	TimerEventMan::Reset();
	Azul::AnimTime start = TimerEventMan::GetTimeCurrent();

	// Load the waves
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Alert, "Alert_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Electro, "Electro_mono.wav");

	// Create the Playlist

	// 1 voice - playlist
	{
		VoiceCallBack* pVoiceCallback = new VoiceCallBack_One();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::Alert, pPlaylistCmd, pVoiceCallback, Wave::ID::Alert);
	}

	// 1 voice - playlist
	{
		VoiceCallBack* pVoiceCallback = new VoiceCallBack_One();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::Electro, pPlaylistCmd, pVoiceCallback, Wave::ID::Electro);
	}

	// How long did the load take?
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - start;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));
	Debug::out("Total Load Time: %d ms \n", ms);
	Audio::WaveTableDump();
}

void Demo5::Execute()
{
	Trace::out("\n");
	Trace::out("--- DEMO 5: Execute() ----\n");

	// Set the start time...
	TimerEventMan::Reset();

	Azul::AnimTime* pDemoTime = new Azul::AnimTime();
	Command* pCmd;

	pCmd = new Demo5_A_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 0 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo5_B_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 15 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo5_B_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 10 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo5_B_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 15 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo5_B_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 20 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo5_B_Command(pDemoTime);
	TimerEventMan::Add(pCmd, 25 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	pCmd = new Demo5_KillCommand(pDemoTime);
	TimerEventMan::Add(pCmd, 60 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

}
