//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUDIO_STOPSOUND_COMMAND_H
#define AUDIO_STOPSOUND_COMMAND_H

#include "Command.h"
#include "Sound.h"

class Audio_StopSound_Command : public Command
{

public:
	// Big 4
	Audio_StopSound_Command() = delete;
	Audio_StopSound_Command(const Audio_StopSound_Command&) = delete;
	Audio_StopSound_Command& operator = (const Audio_StopSound_Command&) = delete;
	~Audio_StopSound_Command() = default;

	Audio_StopSound_Command(Sound::ID sound_id, Sound* pSound);

	virtual void Execute() override;

public:
	// Data
	Sound::ID sound_id;
	Sound* pSound;
};

#endif

// --- End of File ---
