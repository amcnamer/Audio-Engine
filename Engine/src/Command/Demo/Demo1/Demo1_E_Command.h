

#ifndef DEMO1_E_Command_H
#define DEMO1_E_Command_H

#include "Command.h"
#include "AnimTimer.h"

class Demo1_E_Command : public Command
{
public:
	Demo1_E_Command(Azul::AnimTime* pTime);

	Demo1_E_Command() = delete;
	Demo1_E_Command(const Demo1_E_Command&) = default;
	Demo1_E_Command& operator = (const Demo1_E_Command&) = default;
	virtual ~Demo1_E_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
