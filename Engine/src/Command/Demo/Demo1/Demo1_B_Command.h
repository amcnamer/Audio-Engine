

#ifndef DEMO1_B_Command_H
#define DEMO1_B_Command_H

#include "Command.h"
#include "AnimTimer.h"

class Demo1_B_Command : public Command
{
public:
	Demo1_B_Command(Azul::AnimTime* pTime);

	Demo1_B_Command() = delete;
	Demo1_B_Command(const Demo1_B_Command&) = default;
	Demo1_B_Command& operator = (const Demo1_B_Command&) = default;
	virtual ~Demo1_B_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
