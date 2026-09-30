#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "ManBase.h"
#include "DLinkMan.h"
#include "Sound.h"
#include "ASound.h"
#include "CircularData.h"
#include "Command.h"

class UserSoundCallBack;

class SoundManager : public ManBase
{
public:
	static const Sound::Priority DEFAULT_PRIORITY = 200;
	//----------------------------------------------------------------------
	// Constructor
	//----------------------------------------------------------------------
private:
	SoundManager(int reserveNum = 3, int reserveGrow = 1);
	SoundManager() = delete;
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator = (const SoundManager&) = delete;
	~SoundManager();

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static Sound* Add(Sound::ID snd_id, UserSoundCallBack *pUserSoundCallBack, Sound::Priority priority);
	static Sound* Add(Sound::ID snd_id, UserSoundCallBack *pUserSoundCallBack);
	static Sound* Add(Sound::ID snd_id, Sound::Priority priority);
	static Sound* Add(Sound::ID snd_id);

	static Sound* Find(Sound::ID snd_id);

	static void Remove(Sound* pNode);
	static void Dump();

	static void Update();

	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
private:
	static SoundManager* GetInstance();

	//----------------------------------------------------------------------
	// Override Abstract methods
	//----------------------------------------------------------------------
protected:
	DLink* derivedCreateNode() override;


	//----------------------------------------------------------------------
	// Data: unique data for this manager 
	//----------------------------------------------------------------------
private:
	Sound* poNodeCompare;
	static SoundManager* pInstance;
};


#endif // !SOUND_MANAGER_H
