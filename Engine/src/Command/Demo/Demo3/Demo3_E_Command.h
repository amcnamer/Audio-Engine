

#ifndef DEMO3_E_COMMAND_H
#define DEMO3_E_COMMAND_H

#include "Command.h"
#include "AnimTimer.h"

class Demo3_E_Command : public Command
{
public:
	Demo3_E_Command(Azul::AnimTime* pTime);

	Demo3_E_Command() = delete;
	Demo3_E_Command(const Demo3_E_Command&) = default;
	Demo3_E_Command& operator = (const Demo3_E_Command&) = default;
	virtual ~Demo3_E_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
