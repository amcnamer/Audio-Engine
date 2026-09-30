//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUDIO_LOAD_WAVE_COMMAND_H
#define AUDIO_LOAD_WAVE_COMMAND_H

#include "Command.h"
#include "Wave.h"
#include "Internal_FileCB_Command.h"

class Audio_LoadWave_Command : public Command
{
public:
	// Big 4
	Audio_LoadWave_Command() = delete;
	Audio_LoadWave_Command(const Audio_LoadWave_Command&) = delete;
	Audio_LoadWave_Command& operator = (const Audio_LoadWave_Command&) = delete;
	~Audio_LoadWave_Command() = default;

	Audio_LoadWave_Command(Wave::ID id, const char* const pWaveName, Internal_FileCB_Command* pFileCB);

	virtual void Execute() override;

public:
	// Data
	Wave::ID id;
	const char* const pWaveName;
	Internal_FileCB_Command* pIFileCB;
};

#endif

// --- End of File ---