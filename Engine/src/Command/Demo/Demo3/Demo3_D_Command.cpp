

#include "Demo3_D_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"


Demo3_D_Command::Demo3_D_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo3_D_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	Trace::out("\n");
	Debug::out("--- Demo3 D: %dms --- \n", ms);
	Trace::out("\n");

	// Timer: 1 seconds
	//    Snd_D = Play 301 with priority : 50 vol : 10 %
	//    Print the status of the active sound call table

	// ---------------------------------------
	// Play D
	// ---------------------------------------

	Sound* pSndD = SoundManager::Add(Sound::ID::Coma, 50);
	assert(pSndD);

	// Vol & Pan
	assert(pSndD->SetVolume(0.10f) == Handle::Status::SUCCESS);
	assert(pSndD->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndD->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();
}

// --- End of File ---
