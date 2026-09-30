

#ifndef DEMO2_A_Command_H
#define DEMO2_A_Command_H

#include "Command.h"
#include "AnimTimer.h"

class Demo2_A_Command : public Command
{
public:
	Demo2_A_Command(Azul::AnimTime* pTime);

	Demo2_A_Command() = delete;
	Demo2_A_Command(const Demo2_A_Command&) = default;
	Demo2_A_Command& operator = (const Demo2_A_Command&) = default;
	virtual ~Demo2_A_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
