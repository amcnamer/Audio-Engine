
#include "Playlist.h"
#include "PlaylistCommand.h"

PlaylistCommand::PlaylistCommand()
	: pPlaylist(nullptr)
{

}

PlaylistCommand::PlaylistCommand(const PlaylistCommand&)
	: pPlaylist(nullptr)
{
	// playlist needs to be set externally
}

void PlaylistCommand::SetPlaylist(Playlist* _pPlaylist)
{
	assert(_pPlaylist);
	this->pPlaylist = _pPlaylist;
}
