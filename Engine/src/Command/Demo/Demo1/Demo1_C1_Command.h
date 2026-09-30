

#ifndef DEMO1_C1_Command_H
#define DEMO1_C1_Command_H

#include "Command.h"
#include "AnimTimer.h"

class Demo1_C1_Command : public Command
{
public:
	Demo1_C1_Command(Azul::AnimTime* pTime);

	Demo1_C1_Command() = delete;
	Demo1_C1_Command(const Demo1_C1_Command&) = default;
	Demo1_C1_Command& operator = (const Demo1_C1_Command&) = default;
	virtual ~Demo1_C1_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
