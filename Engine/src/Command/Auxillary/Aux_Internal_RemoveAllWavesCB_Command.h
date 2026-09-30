//-----------------------------------------------------------------------------
// Copyright 2053, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef AUX_INTERNAL_REMOVEALLWAVESCALLBACK_COMMAND_H
#define AUX_INTERNAL_REMOVEALLWAVESCALLBACK_COMMAND_H

#include "Command.h"
#include "Internal_FileCB_Command.h"

struct Aux_Internal_RemoveAllWavesCB_Command : public Command
{
	Aux_Internal_RemoveAllWavesCB_Command() = delete;
	Aux_Internal_RemoveAllWavesCB_Command(const Aux_Internal_RemoveAllWavesCB_Command&) = delete;
	Aux_Internal_RemoveAllWavesCB_Command& operator = (const Aux_Internal_RemoveAllWavesCB_Command&) = delete;
	~Aux_Internal_RemoveAllWavesCB_Command() = default;

	Aux_Internal_RemoveAllWavesCB_Command(Internal_FileCB_Command* pIFileCB);

	void Execute() override;


	Internal_FileCB_Command* pIFileCB;
};

#endif

//---  End of File ---

