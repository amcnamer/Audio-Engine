
#include "Audio_SoundEnd_Command.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASoundMan.h"

Audio_SoundEnd_Command::Audio_SoundEnd_Command(Sound::ID id, Sound* _pSound)
	: Command(),
	sound_id(id),
	pSound(_pSound)
{
}


void Audio_SoundEnd_Command::Execute()
{
	assert(this->pSound);

	ASound* pASound = pSound->GetASound();
	assert(pASound);

	//stops and clears sound
	pASound->SoundEnd();

	delete this;
}
