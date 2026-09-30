
#ifndef TIMER_EVENT_H
#define	TIMER_EVENT_H

#include "DLink.h"
#include "Command.h"
#include "AnimTimer.h"

class TimerEvent : public DLink
{
public:
	enum ID
	{
		Demo1_A = 0x66660000,
		Demo1_B,
		Demo1_C,
		Uninitialized
	};

public:

	TimerEvent();
	TimerEvent(const TimerEvent&) = delete;
	TimerEvent& operator = (const TimerEvent&) = delete;
	virtual ~TimerEvent();

	void SetID(ID event_id);
	TimerEvent::ID GetID();

	Azul::AnimTime GetTriggerTime();
	void Process();

	void Set(Command* pCommand, Azul::AnimTime deltaTimeToTrigger);

	bool Compare(DLink* pTarget) override;
	void Dump();
	void Wash();


private:
	void Clear();

	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------

private:
	Command* pCommand;
	ID		id;

	Azul::AnimTime	TriggerTime;
	Azul::AnimTime	DeltaTime;
};


#endif

