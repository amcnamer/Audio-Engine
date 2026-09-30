

#include "Demo3_K_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"


Demo3_K_Command::Demo3_K_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo3_K_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo3 K: %ds --- \n", ms);
	Trace::out("\n");

	// Timer : 8 seconds
	//	  Snd_K = Play 301 with priority : 150 vol : 10 %
	//    Print the status of the active sound call table

	// ---------------------------------------
	// Play K
	// ---------------------------------------

	Sound* pSndK = SoundManager::Add(Sound::ID::Coma, 150);
	assert(pSndK);

	// Vol & Pan
	assert(pSndK->SetVolume(0.10f) == Handle::Status::SUCCESS);
	assert(pSndK->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndK->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();
}

// --- End of File ---
