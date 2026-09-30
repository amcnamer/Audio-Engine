

#include "Demo1_B1_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"

Demo1_B1_Command::Demo1_B1_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo1_B1_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo1 B1: %ds --- \n", ms);
	Trace::out("\n");

	// Timer: 0 seconds
	//    Play 3 Fiddle Sounds first center, then left, then right

	// ---------------------------------------
	// Play A
	// ---------------------------------------

	Sound* pSndA = SoundManager::Add(Sound::ID::Fiddle);
	assert(pSndA);

	// Vol & Pan
	assert(pSndA->SetVolume(0.60f) == Handle::Status::SUCCESS);
	assert(pSndA->Pan(-1.0f) == Handle::Status::SUCCESS);
	// Call the sound
	assert(pSndA->Play() == Handle::Status::SUCCESS);


}
