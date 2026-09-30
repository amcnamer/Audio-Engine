

#include "Demo1_E4_Command.h"
#include "SoundManager.h"
#include "Sound.h"
#include "TimerMan.h"
#include "TimerEventMan.h"
#include "Audio_SoundEnd_Command.h"
#include "QueueMan.h"
Demo1_E4_Command::Demo1_E4_Command(Azul::AnimTime* pTime)
	: pStartTime(pTime)
{
	assert(pTime);
}

void Demo1_E4_Command::Execute()
{
	TimerEventMan::UpdateTimeOnly();
	Sound* pSound = SoundManager::Find(Sound::ID::SongB);
	Azul::AnimTime delta = TimerEventMan::GetTimeCurrent() - pSound->PriorityTable->startTime;
	int ms = Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

	Trace::out("\n");
	Debug::out("--- Demo1 E-B: playing for %d seconds --- \n", ms);
	Trace::out("\n");

	Command* pCommand = new Audio_SoundEnd_Command(Sound::ID::SongB, pSound);
	QueueMan::SendAudio(pCommand);
}
