

#ifndef DEMO2_C_Command_H
#define DEMO2_C_Command_H

#include "Command.h"
#include "AnimTimer.h"

class Demo2_C_Command : public Command
{
public:
	Demo2_C_Command(Azul::AnimTime* pTime);

	Demo2_C_Command() = delete;
	Demo2_C_Command(const Demo2_C_Command&) = default;
	Demo2_C_Command& operator = (const Demo2_C_Command&) = default;
	virtual ~Demo2_C_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
