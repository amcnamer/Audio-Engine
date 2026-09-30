//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Audio_PlaySound_Command.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASoundMan.h"

Audio_PlaySound_Command::Audio_PlaySound_Command(Sound::ID _sound_id, Sound* _pSound)
	: Command(),
	sound_id(_sound_id),
	pSound(_pSound)
{

}


void Audio_PlaySound_Command::Execute()
{
	assert(this->pSound);

	ASound* pASound = pSound->GetASound();
	assert(pASound);

	pASound->Play();

	delete this;
}


// --- End of File ---
