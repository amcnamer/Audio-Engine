
#include "TimerEvent.h"
#include "TimerEventMan.h"
#include "AnimTimer.h"

TimerEvent::TimerEvent()
{
	this->id = TimerEvent::Uninitialized;
	this->pCommand = nullptr;
	this->TriggerTime = Azul::AnimTime(Azul::AnimTime::Duration::ZERO);
	this->DeltaTime = Azul::AnimTime(Azul::AnimTime::Duration::ZERO);
}

void TimerEvent::Process()
{
	// make sure the command is valid
	assert(this->pCommand);

	// fire off command
	this->pCommand->Execute();
}

Azul::AnimTime TimerEvent::GetTriggerTime()
{
	return this->TriggerTime;
}

void TimerEvent::SetID(ID event_id)
{
	this->id = event_id;
}

TimerEvent::ID TimerEvent::GetID()
{
	return this->id;
}

void TimerEvent::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->Clear();
}

void TimerEvent::Set(Command* pCmd, Azul::AnimTime deltaTimeToTrigger)
{
	assert(pCmd);
	this->pCommand = pCmd;

	this->DeltaTime = deltaTimeToTrigger;

	this->TriggerTime = TimerEventMan::GetTimeCurrent() + this->DeltaTime;
}

void TimerEvent::Clear()
{
	this->id = TimerEvent::Uninitialized;
	delete this->pCommand;
	this->pCommand = nullptr;

	this->TriggerTime = Azul::AnimTime(Azul::AnimTime::Duration::ZERO);
	this->DeltaTime = Azul::AnimTime(Azul::AnimTime::Duration::ZERO);

}

bool TimerEvent::Compare(DLink* pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	TimerEvent* pDataB = (TimerEvent*)pTarget;

	bool s = false;

	if (this->id == pDataB->id)
	{
		s = true;
	}

	return s;
}

void TimerEvent::Dump()
{
	// Dump - Print contents to the debug output window
	int ms = Azul::AnimTime::Quotient(this->GetTriggerTime(), Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));

	Trace::out("   Name: %d (%p) %f s\n", this->GetID(), this, (float)ms / 1000.0f);
}

TimerEvent::~TimerEvent()
{
	delete this->pCommand;
}
