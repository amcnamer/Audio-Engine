//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUDIO_VOLUME_UP_OT_COMMAND_H
#define AUDIO_VOLUME_UP_OT_COMMAND_H

#include "Command.h"
#include "Sound.h"

class Audio_VolumeUpOT_Command : public Command
{

public:
	// Big 4
	Audio_VolumeUpOT_Command() = delete;
	Audio_VolumeUpOT_Command(const Audio_VolumeUpOT_Command&) = delete;
	Audio_VolumeUpOT_Command& operator = (const Audio_VolumeUpOT_Command&) = delete;
	~Audio_VolumeUpOT_Command() = default;

	Audio_VolumeUpOT_Command(Sound::ID sound_id, Sound* pSound, float value);

	virtual void Execute() override;

public:
	// Data
	Sound::ID sound_id;
	Sound* pSound;
	float value;
};

#endif

// --- End of File ---
