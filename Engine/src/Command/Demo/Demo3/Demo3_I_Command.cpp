
#include "Demo3_I_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"


Demo3_I_Command::Demo3_I_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo3_I_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo3 I: %ds --- \n", ms);
	Trace::out("\n");

	// Timer : 6 seconds
	//	  Snd_I = Play 301 with priority : 75 vol : 10 %
	//	  Print the status of the active sound call table

	// ---------------------------------------
	// Play I
	// ---------------------------------------

	Sound* pSndI = SoundManager::Add(Sound::ID::Coma, 75);
	assert(pSndI);

	// Vol & Pan
	assert(pSndI->SetVolume(0.10f) == Handle::Status::SUCCESS);
	assert(pSndI->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndI->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();
}

// --- End of File ---
