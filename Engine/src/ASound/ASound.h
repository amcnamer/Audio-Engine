
#ifndef ASOUND_H
#define ASOUND_H

#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "DLink.h"
#include "Sound.h"
#include "Voice.h"
#include "Playlist.h"

class UserSoundCallback;

class ASound : public DLink
{
public:
	// Big 4
	ASound();
	ASound(const ASound&) = delete;
	ASound& operator = (const ASound&) = delete;
	virtual ~ASound();

	void Set(Sound::ID snd_id, Sound* pSnd);

	void Dump();
	void Wash();

	virtual bool Compare(DLink* pTargetNode) override;

	// ---- Commands ---
	void Play();
	void Stop();
	void SetVolume(float vol);
	void GetVolume(float * vol);
	void Pan(float pan);

	// Stop and remove all
	void SoundEnd();

private:
	void Clear();


public:
	//----------------------------------------------------
	// Data
	//----------------------------------------------------

	Playlist* pPlaylist;
	Sound::ID sound_id;
	Sound* pSound;
	UserSoundCallBack* pUserSoundCallback;

	Handle handle;
};

#endif