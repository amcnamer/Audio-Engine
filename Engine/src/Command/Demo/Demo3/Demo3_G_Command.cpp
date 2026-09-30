

#include "Demo3_G_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"


Demo3_G_Command::Demo3_G_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo3_G_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - *this->pStartTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo3 G: %ds --- \n", ms);
	Trace::out("\n");

	// Timer: 4 seconds
	//    Snd_G = Play 301 with priority : 150 vol : 10 %
	//    Print the status of the active sound call table

	// ---------------------------------------
	// Play G
	// ---------------------------------------

	Sound* pSndG = SoundManager::Add(Sound::ID::Coma, 150);
	assert(pSndG);

	// Vol & Pan
	assert(pSndG->SetVolume(0.10f) == Handle::Status::SUCCESS);
	assert(pSndG->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndG->Play() == Handle::Status::SUCCESS);

	// ---------------------------------------
	// Priority Table
	// ---------------------------------------
	Sound::PrintPriorityTable();
}

// --- End of File ---
