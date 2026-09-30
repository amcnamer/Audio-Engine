#ifndef DEMO2_KILL_CMD_H
#define DEMO2_KILL_CMD_H

#include "Command.h"
#include "AnimTimer.h"

class Demo2_KillCommand : public Command
{
public:
	Demo2_KillCommand(Azul::AnimTime* pTime);

	Demo2_KillCommand() = delete;
	Demo2_KillCommand(const Demo2_KillCommand&) = default;
	Demo2_KillCommand& operator = (const Demo2_KillCommand&) = default;
	virtual ~Demo2_KillCommand() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif