
#include "Aux_PlaylistCallBack_Command.h"

Aux_PlaylistCallBack_Command::Aux_PlaylistCallBack_Command(Internal_Playlist_CallBack* _pIFileCB)
	: pPlaylistCB(_pIFileCB)
{
	assert(pPlaylistCB);
}

void Aux_PlaylistCallBack_Command::Execute()
{
	//Debug::out("Aux_PlaylistCB_Cmd::Execute()\n");

	this->pPlaylistCB->Execute();

	delete this;
}

