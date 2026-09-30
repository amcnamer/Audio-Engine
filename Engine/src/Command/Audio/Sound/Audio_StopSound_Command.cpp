//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Audio_StopSound_Command.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASoundMan.h"

Audio_StopSound_Command::Audio_StopSound_Command(Sound::ID _sound_id, Sound* _pSound)
	: Command(),
	sound_id(_sound_id),
	pSound(_pSound)
{

}


void Audio_StopSound_Command::Execute()
{
	assert(this->pSound);

	ASound* pASound = pSound->GetASound();
	assert(pASound);

	pASound->Stop();

	delete this;
}


// --- End of File ---
