

#ifndef Playlist_MAN_H
#define Playlist_MAN_H 

#include "ManBase.h"
#include "DLinkMan.h"
#include "Sound.h"
#include "Playlist.h"
#include "Voice.h"
#include "Wave.h"

class PlaylistMan : public ManBase
{

	//----------------------------------------------------------------------
	// Constructor
	//----------------------------------------------------------------------
private:
	PlaylistMan(int reserveNum = 3, int reserveGrow = 1);

	PlaylistMan() = delete;
	PlaylistMan(const PlaylistMan&) = delete;
	PlaylistMan& operator = (const PlaylistMan&) = delete;
	~PlaylistMan();

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static Playlist* Add(ASound* pASnd,PlaylistCommand* pPlaylistCmd,VoiceCallBack* pVoiceCallbackA,
		Wave::ID VoiceA,VoiceCallBack* pVoiceCallbackB,Wave::ID VoiceB);

	static Playlist* Find(Sound::ID snd_id);

	static void Remove(Playlist* pNode);
	static void Dump();

	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
private:
	static PlaylistMan* GetInstance();

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
	static PlaylistMan* pInstance;

};


#endif