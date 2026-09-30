
#include "Playlist_TwoVoice_Command.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "SoundManager.h"
#include "PlaylistMan.h"

Playlist_TwoVoice_Command::Playlist_TwoVoice_Command()
	: PlaylistCommand()
{

}

Playlist_TwoVoice_Command::Playlist_TwoVoice_Command(const Playlist_TwoVoice_Command&)
	: PlaylistCommand()
{

}

PlaylistCommand* Playlist_TwoVoice_Command::CreateCallbackCopy()
{
	// copy constructor
	return new Playlist_TwoVoice_Command(*this);
}


void Playlist_TwoVoice_Command::Start()
{
	assert(pPlaylist);
	Handle::Status status;
	pPlaylist->pVoiceA->PanVoice(-1.0f);
	pPlaylist->pVoiceB->PanVoice(1.0f);
	status = pPlaylist->pVoiceA->Start();
	assert(status == Handle::Status::SUCCESS);

	// Hint... set one left, one right for milestone
	status = pPlaylist->pVoiceB->Start();
	assert(status == Handle::Status::SUCCESS);
}


void Playlist_TwoVoice_Command::Stop()
{
	assert(pPlaylist);
	Handle::Status status;
	status = pPlaylist->pVoiceA->Stop();
	assert(status == Handle::Status::SUCCESS);
	status = pPlaylist->pVoiceB->Stop();
	assert(status == Handle::Status::SUCCESS);
}

void Playlist_TwoVoice_Command::StopA()
{
	assert(pPlaylist);
	Handle::Status status;
	status = pPlaylist->pVoiceA->Stop();
	assert(status == Handle::Status::SUCCESS);
}

void Playlist_TwoVoice_Command::StopB()
{
	assert(pPlaylist);
	Handle::Status status;
	status = pPlaylist->pVoiceB->Stop();
	assert(status == Handle::Status::SUCCESS);
}

void Playlist_TwoVoice_Command::SoundEnd()
{
	assert(pPlaylist);
	Handle::Status status;

	status = pPlaylist->pVoiceA->Stop();
	assert(status == Handle::Status::SUCCESS);

	status = pPlaylist->pVoiceB->Stop();
	assert(status == Handle::Status::SUCCESS);

	// Now remove it off the active
	PlaylistMan::Remove(pPlaylist);
}

void Playlist_TwoVoice_Command::SetVolume(float vol)
{
	assert(pPlaylist);
	Handle::Status status;
	status = pPlaylist->pVoiceA->SetVolume(vol);
	assert(status == Handle::Status::SUCCESS);
	status = pPlaylist->pVoiceB->SetVolume(vol);
	assert(status == Handle::Status::SUCCESS);
}

void Playlist_TwoVoice_Command::GetVolume(float* volume)
{
	
}

void Playlist_TwoVoice_Command::Pan(float pan)
{
	assert(pPlaylist);
	Handle::Status status;
	status = pPlaylist->pVoiceA->PanVoice(pan);
	assert(status == Handle::Status::SUCCESS);
	status = pPlaylist->pVoiceB->PanVoice(pan);
	assert(status == Handle::Status::SUCCESS);
}