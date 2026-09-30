//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO4_B_COMMAND_H
#define DEMO4_B_COMMAND_H

#include "Command.h"
#include "AnimTimer.h"

class Demo4_B_Command : public Command
{
public:
	Demo4_B_Command(Azul::AnimTime* pTime);

	Demo4_B_Command() = delete;
	Demo4_B_Command(const Demo4_B_Command&) = default;
	Demo4_B_Command& operator = (const Demo4_B_Command&) = default;
	virtual ~Demo4_B_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
