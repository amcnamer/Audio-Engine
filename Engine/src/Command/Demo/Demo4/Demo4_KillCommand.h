#ifndef DEMO4_KILL_CMD_H
#define DEMO4_KILL_CMD_H

#include "Command.h"
#include "AnimTimer.h"

class Demo4_KillCommand : public Command
{
public:
	Demo4_KillCommand() = default;
	Demo4_KillCommand(const Demo4_KillCommand&) = default;
	Demo4_KillCommand& operator = (const Demo4_KillCommand&) = default;
	virtual ~Demo4_KillCommand() = default;

	virtual void Execute() override;

public:
	// Data

};

#endif