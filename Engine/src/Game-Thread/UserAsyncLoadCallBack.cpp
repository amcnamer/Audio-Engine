
#include "UserAsyncLoadCallBack.h"
#include "Sound.h"
#include "TimerMan.h"
#include "StringEnum.h"
#include "TimerEventMan.h"
#include "PlaylistJukeBox.h"
#include "SoundManager.h"
#include "Audio.h"
#include "VoiceCallBack_One.h"
#include "Playlist_OneVoice_Command.h"

UserAsyncLoadCallBack::UserAsyncLoadCallBack()
	:pWaveName{ 0 },
	wave_id{ Wave::ID::Empty },
	timeStart(),
	timeEnd()
{
}

Wave::ID UserAsyncLoadCallBack::GetWaveID()
{
	return this->wave_id;
}

void UserAsyncLoadCallBack::Execute()
{
	assert(this->pWaveName);

	Debug::out("------------------------------\n");
	Debug::out("  UserAsyncLoadCallback(%p) \n", this);
	Debug::out("\n");
	Debug::out("    Wave:ID: %d (%s)\n", this->wave_id, StringMe(this->wave_id));
	Debug::out("       Wave: %s \n", this->pWaveName);


	this->timeEnd = TimerEventMan::GetTimeCurrent();
	Azul::AnimTime delta = this->timeEnd - this->timeStart;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));
	Debug::out("   duration: %f s (%d ms) \n", (float)ms / 1000.0f, ms);

	Debug::out("------------------------------\n");


	// As soon as the Beethoven is loaded from the callback
	//	  Start the Beethoven sound
	//	  SndC = Play 503, vol: 50 %, pan : center, stereo, Priority default (optional)
	//	     Beethoven should start
	//       Debug::out() in the callback
	//	     Print the wave table


	// 1 voice - playlist
	{
		VoiceCallBack* pVoiceCallback = new VoiceCallBack_One();
		PlaylistCommand* pPlaylistCmd = new Playlist_OneVoice_Command();

		PlaylistJukeBox::Load(Sound::ID::Beethoven, pPlaylistCmd, pVoiceCallback, Wave::ID::Beethoven);
	}

	// ---------------------------------------
	// Play C
	// ---------------------------------------

	Sound* pSndC = SoundManager::Add(Sound::ID::Beethoven);
	assert(pSndC);

	// Vol & Pan
	assert(pSndC->SetVolume(15.0f) == Handle::Status::SUCCESS);
	//assert(pSndC->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndC->Play() == Handle::Status::SUCCESS);


	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();
	Audio::WaveTableDump();

}

void UserAsyncLoadCallBack::Set(Wave::ID id, const char* _pWaveName)
{
	memset(this->pWaveName, 0, Wave::NAME_SIZE);
	strcpy_s(this->pWaveName, Wave::NAME_SIZE, _pWaveName);
	this->wave_id = id;
	this->timeStart = TimerEventMan::GetTimeCurrent();
	this->timeEnd = TimerEventMan::GetTimeCurrent();
}

