
#ifndef DEMO3_KILL_COMMAND_H
#define DEMO3_KILL_COMMAND_H

#include "Command.h"
#include "AnimTimer.h"

class Demo3_Kill_Command : public Command
{
public:
	Demo3_Kill_Command(Azul::AnimTime* pTime);

	Demo3_Kill_Command() = delete;
	Demo3_Kill_Command(const Demo3_Kill_Command&) = default;
	Demo3_Kill_Command& operator = (const Demo3_Kill_Command&) = default;
	virtual ~Demo3_Kill_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
