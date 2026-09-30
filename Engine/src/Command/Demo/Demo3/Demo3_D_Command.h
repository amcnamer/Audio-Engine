

#ifndef DEMO3_D_CMD_H
#define DEMO3_D_CMD_H

#include "Command.h"
#include "AnimTimer.h"

class Demo3_D_Command : public Command
{
public:
	Demo3_D_Command(Azul::AnimTime* pTime);

	Demo3_D_Command() = delete;
	Demo3_D_Command(const Demo3_D_Command&) = default;
	Demo3_D_Command& operator = (const Demo3_D_Command&) = default;
	virtual ~Demo3_D_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif
