
#ifndef DEMO3_A_COMMAND_H
#define DEMO3_A_COMMAND_H

#include "Command.h"
#include "AnimTimer.h"

class Demo3_A_Command : public Command
{
public:
	Demo3_A_Command(Azul::AnimTime* pTime);

	Demo3_A_Command() = delete;
	Demo3_A_Command(const Demo3_A_Command&) = default;
	Demo3_A_Command& operator = (const Demo3_A_Command&) = default;
	virtual ~Demo3_A_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif