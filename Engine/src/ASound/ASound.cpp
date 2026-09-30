

#include "ASound.h"
#include "ASoundMan.h"
#include "PlaylistJukeBox.h"
#include "PlaylistMan.h"
#include "StringEnum.h"
#include "SoundManager.h"
#include "Playlist_OneVoice_Command.h"
#include "QueueMan.h"

ASound::ASound()
	:pPlaylist(nullptr),
	sound_id(Sound::ID::Uninitialized),
	pSound(nullptr),
	pUserSoundCallback(nullptr)
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

ASound::~ASound()
{
	//Debug::out("~ASnd()\n");
}


void ASound::SoundEnd()
{
	assert(this->sound_id != Sound::ID::Uninitialized);
	assert(this->pPlaylist);

	// Playlist (which will deal with Voice)
	// 
	// add an abstraction to the playlist
	this->pPlaylist->poCmd->SoundEnd();

	// Sound needs to be alerted
	assert(this->pSound);
	this->pSound->RemoveFromPriorityTable();
	this->pSound->pASound = nullptr;
	SoundManager::Remove(this->pSound);

	// ASoundMan - remove from the active list
	this->pSound = nullptr;
	ASoundMan::Remove(this);
	Debug::out(" <<-- Sound end() ------\n");
}

void ASound::Set(Sound::ID _sound_id, Sound* _pSound)
{
	this->sound_id = _sound_id;

	assert(_pSound);
	this->pSound = _pSound;

	// Do we need mtx projection?
	pSound->Set(this);

	// Find a reference
	Playlist* pPlayRef = PlaylistJukeBox::Find(this->sound_id);
	assert(pPlayRef);

	// Do a deep copy...
	assert(this->sound_id == pPlayRef->id);

	assert(pPlayRef->poCmd);
	PlaylistCommand* pPlaylistCmd = pPlayRef->poCmd->CreateCallbackCopy();
	assert(pPlaylistCmd);

	VoiceCallBack* pCallbackA = nullptr;
	Wave::ID VoiceA = Wave::ID::Not_Used;
	VoiceCallBack* pCallbackB = nullptr;
	Wave::ID VoiceB = Wave::ID::Not_Used;

	if (pPlayRef->pVoiceA)
	{
		// Problem: you don't know what type of callback is being used
		// Answer: ask the class to create one itself
		assert(pPlayRef->pVoiceA);
		assert(pPlayRef->pVoiceA->pCallback);

		pCallbackA = pPlayRef->pVoiceA->pCallback->CreateCallBackCopy();
		VoiceA = pPlayRef->pVoiceA->pWave->id;

		assert(pCallbackA);
	}

	if (pPlayRef->pVoiceB)
	{
		// Problem: you don't know what type of callback is being used
		// Answer: ask the class to create one itself
		assert(pPlayRef->pVoiceB);
		assert(pPlayRef->pVoiceB->pCallback);

		pCallbackB = pPlayRef->pVoiceB->pCallback->CreateCallBackCopy();
		VoiceB = pPlayRef->pVoiceB->pWave->id;

		assert(pCallbackB);
	}
	this->pPlaylist = PlaylistMan::Add(this,pPlaylistCmd,pCallbackA,VoiceA,pCallbackB,VoiceB);

	// Make sure new playlist is TRULY independent
	assert(this->pPlaylist);
}

void ASound::Play()
{
	assert(this->pPlaylist);

	// add an abstraction to the playlist
	this->pPlaylist->poCmd->Start();

	Debug::out("ASound::Play(%p)\n", this);
}


void ASound::Stop()
{
	assert(this->pPlaylist);

	this->pPlaylist->poCmd->Stop();
	Debug::out("ASound::Stop(%p)\n", this);
}

void ASound::SetVolume(float vol)
{
	assert(this->pPlaylist);

	this->pPlaylist->poCmd->SetVolume(vol);


}

void ASound::GetVolume(float* volume)
{
	this->pPlaylist->poCmd->GetVolume(volume);
}

void ASound::Pan(float pan)
{
	assert(this->pPlaylist);

	this->pPlaylist->poCmd->Pan(pan);


}

void ASound::Dump()
{
	// Dump - Print contents to the debug output window
	Trace::out("\t\tASound(%p) %s Playlist(%p)\n", this, StringMe(this->sound_id), this->pPlaylist);
}

void ASound::Clear()
{
	this->pPlaylist = nullptr;
	this->sound_id = Sound::ID::Uninitialized;
}

void ASound::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->Clear();
}

bool ASound::Compare(DLink* pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	ASound* pDataB = (ASound*)pTarget;

	bool status = false;

	if (this->sound_id == pDataB->sound_id)
	{
		status = true;
	}

	return status;
}