

#ifndef DEMO3_F_COMMAND_H
#define DEMO3_F_COMMAND_H

#include "Command.h"
#include "AnimTimer.h"

class Demo3_F_Command : public Command
{
public:
	Demo3_F_Command(Azul::AnimTime* pTime);

	Demo3_F_Command() = delete;
	Demo3_F_Command(const Demo3_F_Command&) = default;
	Demo3_F_Command& operator = (const Demo3_F_Command&) = default;
	virtual ~Demo3_F_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
