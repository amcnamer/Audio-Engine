

#ifndef DEMO2_B_Command_H
#define DEMO2_B_Command_H

#include "Command.h"
#include "AnimTimer.h"

class Demo2_B_Command : public Command
{
public:
	Demo2_B_Command(Azul::AnimTime* pTime);

	Demo2_B_Command() = delete;
	Demo2_B_Command(const Demo2_B_Command&) = default;
	Demo2_B_Command& operator = (const Demo2_B_Command&) = default;
	virtual ~Demo2_B_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
