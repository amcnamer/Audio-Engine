
#include "Playlist_OneVoice_Command.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "SoundManager.h"
#include "PlaylistMan.h"

Playlist_OneVoice_Command::Playlist_OneVoice_Command()
	: PlaylistCommand()
{

}

Playlist_OneVoice_Command::Playlist_OneVoice_Command(const Playlist_OneVoice_Command&)
	: PlaylistCommand()
{

}

PlaylistCommand* Playlist_OneVoice_Command::CreateCallbackCopy()
{
	// copy constructor
	return new Playlist_OneVoice_Command(*this);
}

void Playlist_OneVoice_Command::Start()
{
	assert(pPlaylist);
	Handle::Status status;
	status = pPlaylist->pVoiceA->Start();
	assert(status == Handle::Status::SUCCESS);
}

void Playlist_OneVoice_Command::Stop()
{
	assert(pPlaylist);
	Handle::Status status;
	status = pPlaylist->pVoiceA->Stop();
	assert(status == Handle::Status::SUCCESS);
}

void Playlist_OneVoice_Command::SoundEnd()
{
	assert(pPlaylist);
	Handle::Status status;
	status = pPlaylist->pVoiceA->Stop();
	assert(status == Handle::Status::SUCCESS);

	// Now remove it off the active
	PlaylistMan::Remove(pPlaylist);
}

void Playlist_OneVoice_Command::SetVolume(float vol)
{
	assert(pPlaylist);
	Handle::Status status;
	status = pPlaylist->pVoiceA->SetVolume(vol);
	assert(status == Handle::Status::SUCCESS);
}

void Playlist_OneVoice_Command::GetVolume(float* volume)
{
	assert(pPlaylist);
	Handle::Status status;
	status = pPlaylist->pVoiceA->GetVolume(volume);
	assert(status == Handle::Status::SUCCESS);
}
void Playlist_OneVoice_Command::Pan(float pan)
{
	assert(pPlaylist);
	Handle::Status status;
	status = pPlaylist->pVoiceA->PanVoice(pan);
	assert(status == Handle::Status::SUCCESS);
}