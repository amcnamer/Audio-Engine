
#ifndef DEMO3_G_COMMAND_H
#define DEMO3_G_COMMAND_H

#include "Command.h"
#include "AnimTimer.h"

class Demo3_G_Command : public Command
{
public:
	Demo3_G_Command(Azul::AnimTime* pTime);

	Demo3_G_Command() = delete;
	Demo3_G_Command(const Demo3_G_Command&) = default;
	Demo3_G_Command& operator = (const Demo3_G_Command&) = default;
	virtual ~Demo3_G_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
