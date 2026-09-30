

#include "Demo3_J_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"


Demo3_J_Command::Demo3_J_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo3_J_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo3 J: %ds --- \n", ms);
	Trace::out("\n");

	// Timer: 7 seconds
	//    Snd_J = Play 301 with priority : 75 vol : 10 %
	//    Print the status of the active sound call table

	// ---------------------------------------
	// Play J
	// ---------------------------------------

	Sound* pSndJ = SoundManager::Add(Sound::ID::Coma, 75);
	assert(pSndJ);

	// Vol & Pan
	assert(pSndJ->SetVolume(0.10f) == Handle::Status::SUCCESS);
	assert(pSndJ->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndJ->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();
}

// --- End of File ---
