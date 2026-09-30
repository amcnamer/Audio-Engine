//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef COMMAND_H
#define COMMAND_H

#include "Handle.h"

class Command
{
public:
	enum Type
	{
		Load_Wave,
		Play_Sound,
		Stop_Sound,
		Pause_Sound,
		PanLeft,
		PanRight,
		SetVolume,

		Uninitialized
	};

public:
	// Big 4
	Command() = default;
	Command(const Command&) = default;
	Command& operator = (const Command&) = default;
	virtual ~Command() = default;

	virtual void Execute() = 0;

public:
	// Data

	Handle handle;
};

#endif

// --- End of File ---
