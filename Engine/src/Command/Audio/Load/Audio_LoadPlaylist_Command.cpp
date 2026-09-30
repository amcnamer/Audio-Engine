
#include "Audio_LoadPlaylist_Command.h"
#include "PlaylistJukeBox.h"
#include "Aux_PlaylistCallBack_Command.h"
#include "QueueMan.h"

Audio_LoadPlaylist_Command::Audio_LoadPlaylist_Command(Sound::ID _snd_id,PlaylistCommand* _pPlaylistCmd,
	VoiceCallBack* _pVoiceCallbackA,Wave::ID _VoiceA,VoiceCallBack* _pVoiceCallbackB,Wave::ID _VoiceB, Internal_Playlist_CallBack* pCommand)
	: Command(),snd_id(_snd_id),pPlaylistCmd(_pPlaylistCmd),pVoiceCallbackA(_pVoiceCallbackA),
	VoiceA(_VoiceA),pVoiceCallbackB(_pVoiceCallbackB),VoiceB(_VoiceB), pCallback(pCommand)
	{

	}

void Audio_LoadPlaylist_Command::Execute()
{

	PlaylistJukeBox::Add(snd_id,pPlaylistCmd,pVoiceCallbackA,VoiceA,pVoiceCallbackB,VoiceB);

	Aux_PlaylistCallBack_Command* pCommand = new Aux_PlaylistCallBack_Command(this->pCallback);

	QueueMan::SendAux(pCommand);
	delete this;
}