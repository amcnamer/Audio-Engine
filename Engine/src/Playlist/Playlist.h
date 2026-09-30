
#ifndef Playlist_H
#define Playlist_H

#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "DLink.h"
#include "Sound.h"
#include "Voice.h"
#include "PlaylistCommand.h"
#include "VoiceCallBack.h"


class Playlist : public DLink
{
public:
	enum class Type
	{
		PlayOnce,
		PlayRepeated,
		Stitched,
		Default = PlayOnce,
		Uninitialized
	};

public:
	// Big 4
	Playlist();
	Playlist(const Playlist&) = delete;
	Playlist& operator = (const Playlist&) = delete;
	virtual ~Playlist();

	void Set(ASound* pASnd,PlaylistCommand* pPlaylistCmd,VoiceCallBack* pVoiceCallbackA,
		Wave::ID VoiceA,VoiceCallBack* pVoiceCallbackB,Wave::ID VoiceB);

	void Set(Sound::ID snd_id,PlaylistCommand* pPlaylistCmd,VoiceCallBack* pVoiceCallbackA,
		Wave::ID VoiceA,VoiceCallBack* pVoiceCallbackB,Wave::ID VoiceB);

	void SetId(Sound::ID id);
	Sound::ID GetId() const;

	void Dump();
	void Wash();

	virtual bool Compare(DLink* pTargetNode) override;

private:
	void Clear();
	//void LoadBuffer(const char* const pWaveName);
	//void SetName(const char* const pWaveName);

public:
	//----------------------------------------------------
	// Data
	//----------------------------------------------------

	// In the future it can be many...
	Voice* pVoiceA;
	Voice* pVoiceB;

	// Command pattern
	PlaylistCommand* poCmd;

	Sound::ID id;
	Type    type;

	Handle handle;
};

#endif
