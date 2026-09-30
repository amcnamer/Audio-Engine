//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Audio_PanSoundRightOT_Command.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASoundMan.h"
#include "AnimTimer.h"

Audio_PanSoundRightOT_Command::Audio_PanSoundRightOT_Command(Sound::ID _sound_id, Sound* _pSound, float val)
	: Command(),
	sound_id(_sound_id),
	pSound(_pSound),
	value(val)
{

}


void Audio_PanSoundRightOT_Command::Execute()
{
	assert(this->pSound);

	float delta = 2.0f / 2000.0f;

	ASound* pASound = pSound->GetASound();
	assert(pASound);
	int prev = -1;

	Azul::AnimTimer* pTimer = new AnimTimer();
	pTimer->Tic();

	while (this->value < 1.0f)
	{
		Azul::AnimTime pTime = pTimer->Toc();
		int mili = Azul::AnimTime::Quotient(pTime, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));
		if (mili != prev)
		{
			this->value += delta;
			pASound->Pan(this->value);
			prev = mili;
		}

	}
	delete pTimer;
	pTimer = nullptr;
	delete this;
}


// --- End of File ---
