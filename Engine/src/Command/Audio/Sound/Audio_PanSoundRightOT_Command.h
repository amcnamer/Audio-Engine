//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUDIO_PANSOUND_RIGHT_OT_COMMAND_H
#define AUDIO_PANSOUND_RIGHT_OT_COMMAND_H

#include "Command.h"
#include "Sound.h"

class Audio_PanSoundRightOT_Command : public Command
{

public:
	// Big 4
	Audio_PanSoundRightOT_Command() = delete;
	Audio_PanSoundRightOT_Command(const Audio_PanSoundRightOT_Command&) = delete;
	Audio_PanSoundRightOT_Command& operator = (const Audio_PanSoundRightOT_Command&) = delete;
	~Audio_PanSoundRightOT_Command() = default;

	Audio_PanSoundRightOT_Command(Sound::ID sound_id, Sound* pSound, float value);

	virtual void Execute() override;

public:
	// Data
	Sound::ID sound_id;
	Sound* pSound;
	float value;
};

#endif

// --- End of File ---
