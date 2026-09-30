

#include "Demo3_Kill_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"


Demo3_Kill_Command::Demo3_Kill_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo3_Kill_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	// Its the last part of Demo4 so I can delete pStartTime
	delete this->pStartTime;

	// Timer: 13 seconds
	//    Print the status of the active sound call table(see example)
	//    Stop all pending sounds
	//    Print AGAIN the status of the active sound call table

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();

	// ---------------------------------------
	// Kill All
	// ---------------------------------------

	Sound::KillAllActive();

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();

	Trace::out("\n");
	Debug::out("--- Demo3 Kill: %d ms --- \n", ms);
	Trace::out("\n");
}

// --- End of File ---
