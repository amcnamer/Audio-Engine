

#include "Demo1_E_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"

Demo1_E_Command::Demo1_E_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo1_E_Command::Execute()
{

	// Timer: 0 seconds
	//    SndA = Play 401, pan : 0% , StitchedCallBack

	// ---------------------------------------
	// Play A
	// ---------------------------------------

	Sound* pSndA = SoundManager::Add(Sound::ID::SongA);
	assert(pSndA);

	// Vol & Pan
	assert(pSndA->SetVolume(0.70f) == Handle::Status::SUCCESS);
	assert(pSndA->Pan(-1.0f) == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Play A
	// ---------------------------------------

	Sound* pSndB = SoundManager::Add(Sound::ID::SongB);
	assert(pSndB);

	// Vol & Pan
	assert(pSndB->SetVolume(0.70f) == Handle::Status::SUCCESS);
	assert(pSndB->Pan(1.0f) == Handle::Status::SUCCESS);

	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo1 E: %ds --- \n", ms);
	Trace::out("\n");

	pSndA->PriorityTable->startTime = delta;
	pSndB->PriorityTable->startTime = delta;

	// Call the sound
	assert(pSndA->Play() == Handle::Status::SUCCESS);
	assert(pSndB->Play() == Handle::Status::SUCCESS);
	pSndA->PriorityTable->startTime = delta;
	pSndB->PriorityTable->startTime = delta;
}
