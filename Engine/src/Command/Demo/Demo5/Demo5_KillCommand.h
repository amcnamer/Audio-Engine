#ifndef DEMO5_KILL_CMD_H
#define DEMO5_KILL_CMD_H

#include "Command.h"
#include "AnimTimer.h"

class Demo5_KillCommand : public Command
{
public:
	Demo5_KillCommand(Azul::AnimTime* pTime);

	Demo5_KillCommand() = delete;
	Demo5_KillCommand(const Demo5_KillCommand&) = default;
	Demo5_KillCommand& operator = (const Demo5_KillCommand&) = default;
	virtual ~Demo5_KillCommand() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif