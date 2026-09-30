
#ifndef Playlist_TWO_VOICE_COMMAND_H
#define Playlist_TWO_VOICE_COMMAND_H

#include "PlaylistCommand.h"

class Playlist;

class Playlist_TwoVoice_Command : public PlaylistCommand
{
public:
	// Big 4
	Playlist_TwoVoice_Command();
	Playlist_TwoVoice_Command(const Playlist_TwoVoice_Command&);
	Playlist_TwoVoice_Command& operator = (const Playlist_TwoVoice_Command&) = delete;
	~Playlist_TwoVoice_Command() = default;

	PlaylistCommand* CreateCallbackCopy() override;

	// add more
	virtual void Start() override;
	virtual void Stop()  override;
	virtual void StopA();
	virtual void StopB();
	virtual void SetVolume(float vol) override;
	virtual void GetVolume(float* vol) override;
	virtual void Pan(float pan) override;
	virtual void SoundEnd() override;

	// Data

};

#endif