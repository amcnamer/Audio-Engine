
#ifndef AUDIO_LOAD_PLAYLIST_COMMAND_H
#define AUDIO_LOAD_PLAYLIST_COMMAND_H

#include "Command.h"
#include "Sound.h"
#include "Wave.h"
#include "Playlist.h"
#include "Internal_Playlist_CallBack.h"

class Audio_LoadPlaylist_Command : public Command
{

public:
	// Big 4
	Audio_LoadPlaylist_Command() = delete;
	Audio_LoadPlaylist_Command(const Audio_LoadPlaylist_Command&) = delete;
	Audio_LoadPlaylist_Command& operator = (const Audio_LoadPlaylist_Command&) = delete;
	~Audio_LoadPlaylist_Command() = default;

	Audio_LoadPlaylist_Command(Sound::ID snd_id,PlaylistCommand* pPlaylistCmd,VoiceCallBack* pVoiceCallbackA,
		Wave::ID VoiceA,VoiceCallBack* pVoiceCallbackB,Wave::ID VoiceB, Internal_Playlist_CallBack* pCallBack);

	virtual void Execute() override;

public:
	// Data
	Sound::ID snd_id;
	PlaylistCommand* pPlaylistCmd;
	VoiceCallBack* pVoiceCallbackA;
	Wave::ID VoiceA;
	VoiceCallBack* pVoiceCallbackB;
	Wave::ID VoiceB;
	Internal_Playlist_CallBack* pCallback;
};

#endif