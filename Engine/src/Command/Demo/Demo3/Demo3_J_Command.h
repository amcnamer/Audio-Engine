

#ifndef DEMO3_J_COMMAND_H
#define DEMO3_J_COMMAND_H

#include "Command.h"
#include "AnimTimer.h"

class Demo3_J_Command : public Command
{
public:
	Demo3_J_Command(Azul::AnimTime* pTime);

	Demo3_J_Command() = delete;
	Demo3_J_Command(const Demo3_J_Command&) = default;
	Demo3_J_Command& operator = (const Demo3_J_Command&) = default;
	virtual ~Demo3_J_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
