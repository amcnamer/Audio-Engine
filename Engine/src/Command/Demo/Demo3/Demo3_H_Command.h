

#ifndef DEMO3_H_COMMAND_H
#define DEMO3_H_COMMAND_H

#include "Command.h"
#include "AnimTimer.h"

class Demo3_H_Command : public Command
{
public:
	Demo3_H_Command(Azul::AnimTime* pTime);

	Demo3_H_Command() = delete;
	Demo3_H_Command(const Demo3_H_Command&) = default;
	Demo3_H_Command& operator = (const Demo3_H_Command&) = default;
	virtual ~Demo3_H_Command() = default;

	virtual void Execute() override;

public:
	// Data
	Azul::AnimTime* pStartTime;

};

#endif

// --- End of File ---
