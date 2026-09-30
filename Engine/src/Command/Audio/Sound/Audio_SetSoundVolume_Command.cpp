//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Audio_SetSoundVolume_Command.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASoundMan.h"

Audio_SetSoundVolume_Command::Audio_SetSoundVolume_Command(Sound::ID _sound_id,Sound* _pSound, float val)
	: Command(),
	sound_id(_sound_id),
	pSound(_pSound),
	value(val)
{
}


void Audio_SetSoundVolume_Command::Execute()
{
	assert(this->pSound);

	ASound* pASound = pSound->GetASound();
	assert(pASound);

	pASound->SetVolume(this->value);

	delete this;
}


// --- End of File ---
