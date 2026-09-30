
#ifndef PLAYLIST_ONE_VOICE_COMMAND_H
#define PLAYLIST_ONE_VOICE_COMMAND_H

#include "PlaylistCommand.h"

class Playlist;

class Playlist_OneVoice_Command : public PlaylistCommand
{

public:
	// Big 4
	Playlist_OneVoice_Command();
	Playlist_OneVoice_Command(const Playlist_OneVoice_Command&);
	Playlist_OneVoice_Command& operator = (const Playlist_OneVoice_Command&) = delete;
	~Playlist_OneVoice_Command() = default;

	PlaylistCommand* CreateCallbackCopy() override;

	// add more
	virtual void Start() override;
	virtual void Stop() override;
	virtual void SetVolume(float vol) override;
	virtual void GetVolume(float* vol) override;
	virtual void Pan(float pan) override;
	virtual void SoundEnd() override;

public:
	// Data

};

#endif
