
#ifndef DEMO5_B_COMMAND_H
#define DEMO5_B_COMMAND_H

#include "Command.h"
#include "AnimTimer.h"

class Demo5_B_Command : public Command
{
public:
	Demo5_B_Command(Azul::AnimTime* pTime);

	Demo5_B_Command() = delete;
	Demo5_B_Command(const Demo5_B_Command&) = default;
	Demo5_B_Command& operator = (const Demo5_B_Command&) = default;
	virtual ~Demo5_B_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif