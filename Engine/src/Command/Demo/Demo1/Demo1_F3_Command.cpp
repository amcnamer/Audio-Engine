

#include "Demo1_F3_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"
#include "Audio.h"

Demo1_F3_Command::Demo1_F3_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo1_F3_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	Trace::out("\n");
	Debug::out("--- Demo1 F-D: %dms --- \n", ms);
	Trace::out("\n");


	Sound::KillAllActive();

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
