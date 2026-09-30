#ifndef DEMO1_KILL_CMD_H
#define DEMO1_KILL_CMD_H

#include "Command.h"
#include "AnimTimer.h"

class Demo1_KillCommand : public Command
{
public:
	Demo1_KillCommand(Azul::AnimTime* pTime);

	Demo1_KillCommand() = delete;
	Demo1_KillCommand(const Demo1_KillCommand&) = default;
	Demo1_KillCommand& operator = (const Demo1_KillCommand&) = default;
	virtual ~Demo1_KillCommand() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif