
#ifndef Playlist_JUKEBOX_H
#define Playlist_JUKEBOX_H 

#include "ManBase.h"
#include "DLinkMan.h"
#include "Sound.h"
#include "Playlist.h"
#include "Voice.h"
#include "Wave.h"

class PlaylistJukeBox : public ManBase
{

	//----------------------------------------------------------------------
	// Constructor
	//----------------------------------------------------------------------
private:
	PlaylistJukeBox(int reserveNum = 3, int reserveGrow = 1);
	PlaylistJukeBox() = delete;
	PlaylistJukeBox(const PlaylistJukeBox&) = delete;
	PlaylistJukeBox& operator = (const PlaylistJukeBox&) = delete;
	~PlaylistJukeBox();

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static void Load(Sound::ID snd_id,PlaylistCommand* pPlaylistCmd,VoiceCallBack* pVoiceCallback,
		Wave::ID VoiceA,VoiceCallBack* pVoiceCallbackB = nullptr,Wave::ID VoiceB = Wave::ID::Not_Used);


	static Playlist* Add(Sound::ID snd_id,PlaylistCommand* pPlaylistCmd,VoiceCallBack* pVoiceCallbackA,
		Wave::ID VoiceA,VoiceCallBack* pVoiceCallbackB,Wave::ID VoiceB);

	static Playlist* Find(Sound::ID snd_id);

	static void Remove(Playlist* pNode);
	static void Dump();

	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
private:
	static PlaylistJukeBox* GetInstance();

	//----------------------------------------------------------------------
	// Override Abstract methods
	//----------------------------------------------------------------------
protected:
	DLink* derivedCreateNode() override;


	//----------------------------------------------------------------------
	// Data: unique data for this manager 
	//----------------------------------------------------------------------
private:
	Playlist* poNodeCompare;
	static PlaylistJukeBox* pInstance;

};


#endif