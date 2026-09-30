//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef AUX_INTERNAL_PLAYLIST_CALLBACK_COMMAND_H
#define AUX_INTERNAL_PLAYLIST_CALLBACK_COMMAND_H

#include "Command.h"
#include "Internal_Playlist_CallBack.h"

struct Aux_PlaylistCallBack_Command : public Command
{
	Aux_PlaylistCallBack_Command() = delete;
	Aux_PlaylistCallBack_Command(const Aux_PlaylistCallBack_Command&) = delete;
	Aux_PlaylistCallBack_Command& operator = (const Aux_PlaylistCallBack_Command&) = delete;
	~Aux_PlaylistCallBack_Command() = default;

	Aux_PlaylistCallBack_Command(Internal_Playlist_CallBack* pIFileCB);

	

	void Execute() override;


	Internal_Playlist_CallBack* pPlaylistCB;
};

#endif

//---  End of File ---

