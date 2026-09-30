

#include "TimerEventMan.h"
#include "Audio.h"
#include "PlaylistJukeBox.h"
#include "TimerMan.h"
#include "VoiceCallBack_One.h"
#include "Playlist_OneVoice_Command.h"
#include "Sound.h"
#include "GameCallBackA.h"
#include "GameCallBackB.h"
#include "GameCallBackC.h"
#include "GameCallBackD.h"

#include "Demo4.h"
#include "Demo4_A_Command.h"
#include "Demo4_B_Command.h"

Demo4::Demo4(Azul::AnimTime time)
	: Demo(time)
{
	Trace::out("\n");
	Trace::out("******************************\n");
	Trace::out("**  DEMO 4 - User Callback  **\n");
	Trace::out("******************************\n");
}

Demo4::~Demo4()
{

}

void Demo4::Load()
{
	Trace::out("\n");
	Debug::out("--- DEMO 4: Load() ----\n");
	Trace::out("\n");

	TimerEventMan::Reset();
	Azul::AnimTime start = TimerEventMan::GetTimeCurrent();

	Debug::out("Start Load \n");

	// Load the waves
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Dial, "Dial_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::MoonPatrol, "MoonPatrol_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Sequence, "Sequence1_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Donkey, "Donkey_mono.wav");

	// 1 voice - playlist
	{
		VoiceCallBack* pVoiceCallback = new GameCallBackA();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::Dial, pPlaylistCmd, pVoiceCallback, Wave::ID::Dial);
	}

	// 2 voice - playlist
	{
		VoiceCallBack* pVoiceCallback = new GameCallBackB();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::MoonPatrol, pPlaylistCmd, pVoiceCallback, Wave::ID::MoonPatrol);
	}

	// 3 voice - playlist
	{
		VoiceCallBack* pVoiceCallback = new GameCallBackC();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::Sequence, pPlaylistCmd, pVoiceCallback, Wave::ID::Sequence);
	}

	// 4 voice - playlist
	{
		VoiceCallBack* pVoiceCallback = new GameCallBackD();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::Donkey, pPlaylistCmd, pVoiceCallback, Wave::ID::Donkey);
	}

	// How long did it take?
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - start;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));
	Debug::out("Total Load Time: %d ms \n", ms);

}

void Demo4::Execute()
{
	Trace::out("\n");
	Trace::out("--- DEMO 4: Execute() ----\n");

	// Set the start time...
	TimerEventMan::Reset();

	Azul::AnimTime* pDemoTime = new Azul::AnimTime();
	Command* pCmd;

	pCmd = new Demo4_A_Command(pDemoTime);
	assert(pCmd);

	TimerEventMan::Add(pCmd, 0 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	pCmd = new Demo4_B_Command(pDemoTime);
	assert(pCmd);

	TimerEventMan::Add(pCmd, 3500 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));


}

// --- End of File ---