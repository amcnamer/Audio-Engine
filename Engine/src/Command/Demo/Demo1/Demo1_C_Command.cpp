

#include "Demo1_C_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"


Demo1_C_Command::Demo1_C_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo1_C_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	float pan = -1.0f;

	Trace::out("\n");
	Debug::out("--- Demo1 C: %ds --- \n", ms);
	Trace::out("\n");

	// Timer: 0 seconds
	//    SndA = Play 401, pan : 0% , StitchedCallBack

	// ---------------------------------------
	// Play A
	// ---------------------------------------

	Sound* pSndA = SoundManager::Add(Sound::ID::Bassoon);
	assert(pSndA);

	// Vol & Pan
	assert(pSndA->SetVolume(0.60f) == Handle::Status::SUCCESS);
	assert(pSndA->Pan(pan) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndA->Play() == Handle::Status::SUCCESS);

	assert(pSndA->PanRightOverTime(pan) == Handle::Status::SUCCESS);

}
