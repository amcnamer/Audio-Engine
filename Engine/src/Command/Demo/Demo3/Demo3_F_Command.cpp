

#include "Demo3_F_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"


Demo3_F_Command::Demo3_F_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo3_F_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo3 F: %ds --- \n", ms);
	Trace::out("\n");

	// Timer : 3 seconds
	//	  Snd_F = Play 301 with priority : 100 vol : 10 %
	//    Print the status of the active sound call table

	// ---------------------------------------
	// Play F
	// ---------------------------------------

	Sound* pSndF = SoundManager::Add(Sound::ID::Coma, 100);
	assert(pSndF);

	// Vol & Pan
	assert(pSndF->SetVolume(0.10f) == Handle::Status::SUCCESS);
	assert(pSndF->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndF->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();
}

// --- End of File ---
