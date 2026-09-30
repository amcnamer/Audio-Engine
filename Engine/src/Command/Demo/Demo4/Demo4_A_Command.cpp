

#include "Demo4_A_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"

Demo4_A_Command::Demo4_A_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo4_A_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	Trace::out("\n");
	Debug::out("--- Demo4 A: %dms --- \n", ms);
	Trace::out("\n");

	// Timer: 0 seconds
	//    SndA = Play 401, pan : 100 % left, GameCallback_A
	//    SndB = Play 402, pan : 100 % right, GameCallback_B
	//    SndC = Play 403, pan : 100 % left, GameCallback_C

	// ---------------------------------------
	// Play A
	// ---------------------------------------

	Sound* pSndA = SoundManager::Add(Sound::ID::Dial);
	assert(pSndA);

	// Vol & Pan
	assert(pSndA->SetVolume(0.60f) == Handle::Status::SUCCESS);
	assert(pSndA->Pan(-1.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndA->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Play B
	// ---------------------------------------

	//check example for usercallback example to add to the ::Add below

	Sound* pSndB = SoundManager::Add(Sound::ID::MoonPatrol);
	assert(pSndB);

	// Vol & Pan
	assert(pSndB->SetVolume(0.60f) == Handle::Status::SUCCESS);
	assert(pSndB->Pan(1.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndB->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Play C
	// ---------------------------------------

	Sound* pSndC = SoundManager::Add(Sound::ID::Sequence);
	assert(pSndC);

	// Vol & Pan
	assert(pSndC->SetVolume(0.60f) == Handle::Status::SUCCESS);
	assert(pSndC->Pan(-1.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndC->Play() == Handle::Status::SUCCESS);

}