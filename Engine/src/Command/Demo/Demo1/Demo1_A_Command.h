

#ifndef DEMO1_A_Command_H
#define DEMO1_A_Command_H

#include "Command.h"
#include "AnimTimer.h"

class Demo1_A_Command : public Command
{
public:

	Demo1_A_Command() = default;
	Demo1_A_Command(const Demo1_A_Command&) = default;
	Demo1_A_Command& operator = (const Demo1_A_Command&) = default;
	virtual ~Demo1_A_Command() = default;

	virtual void Execute() override;

public:
	// Data
};

#endif

// --- End of File ---
