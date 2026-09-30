

#ifndef DEMO2_D_Command_H
#define DEMO2_D_Command_H

#include "Command.h"
#include "AnimTimer.h"

class Demo2_D_Command : public Command
{
public:
	Demo2_D_Command(Azul::AnimTime* pTime);

	Demo2_D_Command() = delete;
	Demo2_D_Command(const Demo2_D_Command&) = default;
	Demo2_D_Command& operator = (const Demo2_D_Command&) = default;
	virtual ~Demo2_D_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
