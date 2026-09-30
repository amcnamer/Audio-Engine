

#include "Demo4_B_Command.h"
#include "TimerMan.h"
#include "TimerEventMan.h"
#include "Sound.h"
#include "SoundManager.h"

Demo4_B_Command::Demo4_B_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo4_B_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	Trace::out("\n");
	Debug::out("--- Demo4 B: %d ms --- \n", ms);
	Trace::out("\n");

	// Its the last part of Demo4 so I can delete pStartTime
	delete this->pStartTime;

	//Timer: 3.5 seconds
	//   SndD = Play 404, pan : 100 % right, GameCallback_D

	// ---------------------------------------
	// Play D
	// ---------------------------------------

	Sound* pSndD = SoundManager::Add(Sound::ID::Donkey);
	assert(pSndD);

	// Vol & Pan
	assert(pSndD->SetVolume(0.60f) == Handle::Status::SUCCESS);
	assert(pSndD->Pan(1.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndD->Play() == Handle::Status::SUCCESS);

}

// --- End of File ---
