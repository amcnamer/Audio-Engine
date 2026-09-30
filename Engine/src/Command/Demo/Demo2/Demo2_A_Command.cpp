

#include "Demo2_A_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"

Demo2_A_Command::Demo2_A_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo2_A_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	Trace::out("\n");
	Debug::out("--- Demo4 A: %dms --- \n", ms);
	Trace::out("\n");

	// Timer: 0 seconds
	//    SndA = Play 401, pan : 0% , StitchedCallBack

	// ---------------------------------------
	// Play A
	// ---------------------------------------

	Sound* pSndA = SoundManager::Add(Sound::ID::Intro);
	assert(pSndA);

	// Vol & Pan
	assert(pSndA->SetVolume(0.60f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndA->Play() == Handle::Status::SUCCESS);


}
