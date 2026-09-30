//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUDIO_PANSOUND_COMMAND_H
#define AUDIO_PANSOUND_COMMAND_H

#include "Command.h"
#include "Sound.h"

class Audio_PanSound_Command : public Command
{

public:
	// Big 4
	Audio_PanSound_Command() = delete;
	Audio_PanSound_Command(const Audio_PanSound_Command&) = delete;
	Audio_PanSound_Command& operator = (const Audio_PanSound_Command&) = delete;
	~Audio_PanSound_Command() = default;

	Audio_PanSound_Command(Sound::ID sound_id, Sound* pSound, float value);

	virtual void Execute() override;

public:
	// Data
	Sound::ID sound_id;
	Sound* pSound;
	float value;
};

#endif

// --- End of File ---
