
#include "Demo5_B_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"

Demo5_B_Command::Demo5_B_Command(Azul::AnimTime* pTime)
	:pStartTime(pTime)
{
}

void Demo5_B_Command::Execute()
{

	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	Trace::out("\n");
	Debug::out("--- Demo5: Play (%d ms) --- \n", ms);
	Trace::out("\n");

	// Timer: 5 seconds
	//    SndB = Play 502, vol : 30 %, pan : 100 % left, Priority default 
	//    Add Debug::out() to show the call on the correct thread

	// ---------------------------------------
	// Play B
	// ---------------------------------------
	Sound* pSndB = SoundManager::Add(Sound::ID::Alert);
	assert(pSndB);

	// Vol & Pan
	assert(pSndB->SetVolume(0.30f) == Handle::Status::SUCCESS);
	assert(pSndB->Pan(-1.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndB->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------

	Sound::PrintPriorityTable();
}