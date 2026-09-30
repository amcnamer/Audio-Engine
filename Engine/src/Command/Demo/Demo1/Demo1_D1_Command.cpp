

#include "Demo1_D1_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"
#include "Audio_VolumeDownOT_Command.h"

Demo1_D1_Command::Demo1_D1_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo1_D1_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));


	float volume = 1.0f;


	Trace::out("\n");
	Debug::out("--- Demo1 D-B: %ds --- \n", ms);
	Trace::out("\n");

	// Timer: 0 seconds
	//    SndA = Play 401, pan : 0% , StitchedCallBack

	// ---------------------------------------
	// Play A
	// ---------------------------------------

	Sound* pSndA = SoundManager::Add(Sound::ID::Oboe);
	assert(pSndA);

	// Vol & Pan
	assert(pSndA->SetVolume(volume) == Handle::Status::SUCCESS);

	assert(pSndA->Play() == Handle::Status::SUCCESS);

	assert(pSndA->SetVolumeDownOT(volume) == Handle::Status::SUCCESS);
}
