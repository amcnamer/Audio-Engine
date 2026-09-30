//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUDIO_PLAYSOUND_COMMAND_H
#define AUDIO_PLAYSOUND_COMMAND_H

#include "Command.h"
#include "Sound.h"

class Audio_PlaySound_Command : public Command
{

public:
	// Big 4
	Audio_PlaySound_Command() = delete;
	Audio_PlaySound_Command(const Audio_PlaySound_Command&) = delete;
	Audio_PlaySound_Command& operator = (const Audio_PlaySound_Command&) = delete;
	~Audio_PlaySound_Command() = default;

	Audio_PlaySound_Command(Sound::ID sound_id, Sound* pSound);

	virtual void Execute() override;

public:
	// Data
	Sound::ID sound_id;
	Sound* pSound;
};

#endif

// --- End of File ---

