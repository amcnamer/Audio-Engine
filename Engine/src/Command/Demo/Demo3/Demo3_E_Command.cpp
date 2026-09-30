
#include "Demo3_E_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"


Demo3_E_Command::Demo3_E_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo3_E_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo3 E: %ds --- \n", ms);
	Trace::out("\n");

	// Timer : 2 seconds
	//	  Snd_E = Play 301 with priority : 75 vol : 10 %
	//	  Print the status of the active sound call table

	// ---------------------------------------
	// Play E
	// ---------------------------------------

	Sound* pSndE = SoundManager::Add(Sound::ID::Coma, 75);
	assert(pSndE);

	// Vol & Pan
	assert(pSndE->SetVolume(0.10f) == Handle::Status::SUCCESS);
	assert(pSndE->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndE->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();
}

// --- End of File ---
