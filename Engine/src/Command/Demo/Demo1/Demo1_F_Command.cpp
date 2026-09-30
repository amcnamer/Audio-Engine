

#include "Demo1_F_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"

Demo1_F_Command::Demo1_F_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo1_F_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	Trace::out("\n");
	Debug::out("--- Demo1 F-A: %dms --- \n", ms);
	Trace::out("\n");

	// Timer: 0 seconds
	//    SndA = Play 401, pan : 0% , StitchedCallBack

	// ---------------------------------------
	// Play A
	// ---------------------------------------

	Sound* pSndA = SoundManager::Add(Sound::ID::Bassoon);
	assert(pSndA);

	// Vol & Pan
	assert(pSndA->SetVolume(0.40f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndA->Play() == Handle::Status::SUCCESS);


}
