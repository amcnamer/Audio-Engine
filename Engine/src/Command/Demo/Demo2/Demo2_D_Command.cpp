

#include "Demo2_D_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"

Demo2_D_Command::Demo2_D_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo2_D_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo2 B Pan Center: %ds --- \n", ms);
	Trace::out("\n");

	// Timer: 0 seconds
	//    SndA = Play 401, pan : 0% , StitchedCallBack

	// ---------------------------------------
	// Play A
	// ---------------------------------------

	Sound* pSndA = SoundManager::Find(Sound::ID::Intro);
	assert(pSndA);

	// Vol & Pan
	assert(pSndA->Pan(0.0f) == Handle::Status::SUCCESS);
}
