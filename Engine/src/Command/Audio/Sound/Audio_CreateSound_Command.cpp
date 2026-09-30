
#include "Audio_CreateSound_Command.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASoundMan.h"

Audio_CreateSound_Command::Audio_CreateSound_Command(Sound::ID id, Sound* _pSound, UserSoundCallBack* _pUserSoundCallback)
	: Command(),
	sound_id(id),
	pSound(_pSound),
	pUserSoundCallback(_pUserSoundCallback)
{
	assert(pSound);
}


void Audio_CreateSound_Command::Execute()
{
	assert(this->pSound);

	ASound* pASound = ASoundMan::Add(this->sound_id, this->pSound);
	assert(pASound);

	pASound->pUserSoundCallback = this->pUserSoundCallback;

	//Debug::out("Audio_CreateSound_Command():Sound:%p ASound:%p\n",pSound, pASound);
	delete this;
}
