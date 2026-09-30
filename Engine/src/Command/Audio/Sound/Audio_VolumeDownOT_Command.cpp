//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Audio_VolumeDownOT_Command.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASoundMan.h"
#include "AnimTimer.h"

Audio_VolumeDownOT_Command::Audio_VolumeDownOT_Command(Sound::ID _sound_id, Sound* _pSound, float val)
	: Command(),
	sound_id(_sound_id),
	pSound(_pSound),
	value(val)
{

}


void Audio_VolumeDownOT_Command::Execute()
{
	assert(this->pSound);
	float* pValue = new float(this->value);
	float delta = 1.0f / 2000.0f;

	ASound* pASound = pSound->GetASound();
	assert(pASound);
	int prev = -1;

	Azul::AnimTimer* pTimer = new AnimTimer();
	pTimer->Tic();

	while (*pValue > 0.0f)
	{
		Azul::AnimTime pTime = pTimer->Toc();
		int mili = Azul::AnimTime::Quotient(pTime, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));
		if (mili != prev)
		{
			pASound->GetVolume(pValue);
			*pValue -= delta;
			pASound->SetVolume(*pValue);
			prev = mili;
		}

	}
	delete pValue;
	pValue = nullptr;

	delete pTimer;
	pTimer = nullptr;

	pASound->SoundEnd();
	delete this;
}


// --- End of File ---
