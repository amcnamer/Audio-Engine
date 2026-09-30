

#ifndef DEMO4_A_Command_H
#define DEMO4_A_Command_H

#include "Command.h"
#include "AnimTimer.h"

class Demo4_A_Command : public Command
{
public:
	Demo4_A_Command(Azul::AnimTime* pTime);

	Demo4_A_Command() = delete;
	Demo4_A_Command(const Demo4_A_Command&) = default;
	Demo4_A_Command& operator = (const Demo4_A_Command&) = default;
	virtual ~Demo4_A_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

