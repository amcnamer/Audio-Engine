
#include "Internal_Playlist_CallBack.h"

Internal_Playlist_CallBack::Internal_Playlist_CallBack(bool& DoneFlag)
	: finished(DoneFlag)
{

}

void Internal_Playlist_CallBack::Execute()
{
	Debug::out("Playlist loaded - ready\n");

	this->finished = true;

	delete this;
}

//---  End of File ---
