
#include "XAudio2Wrapper.h"
#include "AudioEngine.h"
#include "Playlist.h"
#include "StringEnum.h"
#include "VoiceMan.h"
#include "ASound.h"
#include "QueueMan.h"

Playlist::Playlist()
	: pVoiceA(nullptr),
	pVoiceB(nullptr),
	poCmd(nullptr),
	id(Sound::ID::Uninitialized),
	type(Playlist::Type::Uninitialized)
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Playlist::~Playlist()
{
	//Debug::out("~Playlist()\n");
	if (this->pVoiceA)
	{
		VoiceMan::Remove(this->pVoiceA);
		this->pVoiceA = nullptr;
	}

	if (this->pVoiceB)
	{
		VoiceMan::Remove(this->pVoiceB);
		this->pVoiceB = nullptr;
	}

	delete this->poCmd;
	this->poCmd = nullptr;

}

void Playlist::SetId(Sound::ID _id)
{
	this->id = _id;
}

Sound::ID Playlist::GetId() const
{
	return this->id;
}

void Playlist::Set(ASound* pASound,PlaylistCommand* pPlaylistCmd,VoiceCallBack* pVoiceCallbackA,
	Wave::ID VoiceA,VoiceCallBack* pVoiceCallbackB,Wave::ID VoiceB)
{
	assert(pASound);
	this->id = pASound->sound_id;
	this->type = Playlist::Type::Uninitialized;

	if (VoiceA != Wave::ID::Not_Used)
	{
		this->pVoiceA = VoiceMan::Add(VoiceA, pVoiceCallbackA);
		assert(this->pVoiceA);

		pVoiceCallbackA->SetVoice(pVoiceA);
		pVoiceCallbackA->SetASound(pASound);
	}

	if (VoiceB != Wave::ID::Not_Used)
	{
		this->pVoiceB = VoiceMan::Add(VoiceB, pVoiceCallbackB);
		assert(this->pVoiceB);

		pVoiceCallbackB->SetVoice(pVoiceB);
		pVoiceCallbackB->SetASound(pASound);
	}

	this->poCmd = pPlaylistCmd;
	this->poCmd->SetPlaylist(this);

	assert(this->poCmd);
}

void Playlist::Set(Sound::ID snd_id,PlaylistCommand* pPlaylistCmd,VoiceCallBack* pVoiceCallbackA,
	Wave::ID VoiceA,VoiceCallBack* pVoiceCallbackB,Wave::ID VoiceB)
{
	this->id = snd_id;
	this->type = Playlist::Type::Uninitialized;

	if (VoiceA != Wave::ID::Not_Used)
	{
		this->pVoiceA = VoiceMan::Add(VoiceA, pVoiceCallbackA);
		assert(this->pVoiceA);

		pVoiceCallbackA->SetVoice(pVoiceA);
	}

	if (VoiceB != Wave::ID::Not_Used)
	{
		this->pVoiceB = VoiceMan::Add(VoiceB, pVoiceCallbackB);
		assert(this->pVoiceB);

		pVoiceCallbackB->SetVoice(pVoiceB);
	}

	this->poCmd = pPlaylistCmd;
	this->poCmd->SetPlaylist(this);

	assert(this->poCmd);
}

void Playlist::Dump()
{
	// Dump - Print contents to the debug output window
//	Trace::out("\t\tPlaylist(%p) %s Voice(%p) src:%p\n", this, StringMe(this->id), this->pVoice, this->pVoice->poSourceVoice);
}

void Playlist::Clear()
{
	// This method... is used in wash to reuse 
	// If its alive... remove the data
	if (this->pVoiceA)
	{
		VoiceMan::Remove(this->pVoiceA);
		this->pVoiceA = nullptr;
	}

	if (this->pVoiceB)
	{
		VoiceMan::Remove(this->pVoiceB);
		this->pVoiceB = nullptr;
	}

	delete this->poCmd;
	this->poCmd = nullptr;


	this->id = Sound::ID::Uninitialized;

}

void Playlist::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->Clear();
}

bool Playlist::Compare(DLink* pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	Playlist* pDataB = (Playlist*)pTarget;

	bool status = false;

	if (this->id == pDataB->id)
	{
		status = true;
	}

	return status;
}

