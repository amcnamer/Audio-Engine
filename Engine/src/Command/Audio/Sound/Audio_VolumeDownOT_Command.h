//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUDIO_VOLUME_DOWN_OT_COMMAND_H
#define AUDIO_VOLUME_DOWN_OT_COMMAND_H

#include "Command.h"
#include "Sound.h"

class Audio_VolumeDownOT_Command : public Command
{

public:
	// Big 4
	Audio_VolumeDownOT_Command() = delete;
	Audio_VolumeDownOT_Command(const Audio_VolumeDownOT_Command&) = delete;
	Audio_VolumeDownOT_Command& operator = (const Audio_VolumeDownOT_Command&) = delete;
	~Audio_VolumeDownOT_Command() = default;

	Audio_VolumeDownOT_Command(Sound::ID sound_id, Sound* pSound, float value);

	virtual void Execute() override;

public:
	// Data
	Sound::ID sound_id;
	Sound* pSound;
	float value;
};

#endif

// --- End of File ---
