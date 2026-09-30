

#include "Demo1_E2_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"

Demo1_E2_Command::Demo1_E2_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo1_E2_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Sound* pSound = SoundManager::Find(Sound::ID::SongA);
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - pSound->PriorityTable->startTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo1 E-A: playing for %d seconds --- \n", ms);
	Trace::out("\n");
}
