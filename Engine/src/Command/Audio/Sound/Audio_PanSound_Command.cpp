//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Audio_PanSound_Command.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASoundMan.h"

Audio_PanSound_Command::Audio_PanSound_Command(Sound::ID _sound_id, Sound* _pSound, float val)
	: Command(),
	sound_id(_sound_id),
	pSound(_pSound),
	value(val)
{

}


void Audio_PanSound_Command::Execute()
{
	assert(this->pSound);

	ASound* pASound = pSound->GetASound();
	assert(pASound);

	pASound->Pan(this->value);

	delete this;
}


// --- End of File ---
