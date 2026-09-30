
#ifndef Playlist_COMMAND_H
#define Playlist_COMMAND_H

#include "Handle.h"

class Playlist;

class PlaylistCommand
{
public:
	// Big 4
	PlaylistCommand();
	PlaylistCommand(const PlaylistCommand&);
	PlaylistCommand& operator = (const PlaylistCommand&) = default;
	virtual ~PlaylistCommand() = default;

	void SetPlaylist(Playlist* pPlaylist);
	virtual PlaylistCommand* CreateCallbackCopy() = 0;

	// add more
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void SetVolume(float vol) = 0;
	virtual void GetVolume(float* vol) = 0;
	virtual void Pan(float pan) = 0;
	virtual void SoundEnd() = 0;


protected:
	// Data
	Playlist* pPlaylist;

};

#endif