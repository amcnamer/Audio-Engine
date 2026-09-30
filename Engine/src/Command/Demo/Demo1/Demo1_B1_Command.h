

#ifndef DEMO1_B1_Command_H
#define DEMO1_B1_Command_H

#include "Command.h"
#include "AnimTimer.h"

class Demo1_B1_Command : public Command
{
public:
	Demo1_B1_Command(Azul::AnimTime* pTime);

	Demo1_B1_Command() = delete;
	Demo1_B1_Command(const Demo1_B1_Command&) = default;
	Demo1_B1_Command& operator = (const Demo1_B1_Command&) = default;
	virtual ~Demo1_B1_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
