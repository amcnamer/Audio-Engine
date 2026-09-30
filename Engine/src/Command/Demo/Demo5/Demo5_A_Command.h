
#ifndef DEMO5_A_COMMAND_H
#define DEMO5_A_COMMAND_H

#include "Command.h"
#include "AnimTime.h"

class Demo5_A_Command : public Command
{
public:
	Demo5_A_Command(Azul::AnimTime* pTime);

	Demo5_A_Command() = delete;
	Demo5_A_Command(const Demo5_A_Command&) = default;
	Demo5_A_Command& operator = (const Demo5_A_Command&) = default;
	virtual ~Demo5_A_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
