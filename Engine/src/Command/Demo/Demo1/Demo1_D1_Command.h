

#ifndef DEMO1_D1_Command_H
#define DEMO1_D1_Command_H

#include "Command.h"
#include "AnimTimer.h"

class Demo1_D1_Command : public Command
{
public:
	Demo1_D1_Command(Azul::AnimTime* pTime);

	Demo1_D1_Command() = delete;
	Demo1_D1_Command(const Demo1_D1_Command&) = default;
	Demo1_D1_Command& operator = (const Demo1_D1_Command&) = default;
	virtual ~Demo1_D1_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
