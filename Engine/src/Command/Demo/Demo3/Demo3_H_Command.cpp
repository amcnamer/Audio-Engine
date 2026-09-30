

#include "Demo3_H_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"


Demo3_H_Command::Demo3_H_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo3_H_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo3 H: %ds --- \n", ms);
	Trace::out("\n");

	// Timer: 5 seconds
	//    Snd_H = Play 301 with priority : 75 vol : 10 %
	//    Print the status of the active sound call table

	// ---------------------------------------
	// Play H
	// ---------------------------------------

	Sound* pSndH = SoundManager::Add(Sound::ID::Coma, 75);
	assert(pSndH);

	// Vol & Pan
	assert(pSndH->SetVolume(0.10f) == Handle::Status::SUCCESS);
	assert(pSndH->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndH->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();
}

// --- End of File ---
