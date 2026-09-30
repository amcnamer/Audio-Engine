

#ifndef DEMO3_K_COMMAND_H
#define DEMO3_K_COMMAND_H

#include "Command.h"
#include "AnimTimer.h"

class Demo3_K_Command : public Command
{
public:
	Demo3_K_Command(Azul::AnimTime* pTime);

	Demo3_K_Command() = delete;
	Demo3_K_Command(const Demo3_K_Command&) = default;
	Demo3_K_Command& operator = (const Demo3_K_Command&) = default;
	virtual ~Demo3_K_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
