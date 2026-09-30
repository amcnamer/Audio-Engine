//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUDIO_SETSOUNDVOLUME_COMMAND_H
#define AUDIO_SETSOUNDVOLUME_COMMAND_H


#include "Command.h"
#include "Sound.h"

class Audio_SetSoundVolume_Command : public Command
{

public:
	// Big 4
	Audio_SetSoundVolume_Command() = delete;
	Audio_SetSoundVolume_Command(const Audio_SetSoundVolume_Command&) = delete;
	Audio_SetSoundVolume_Command& operator = (const Audio_SetSoundVolume_Command&) = delete;
	~Audio_SetSoundVolume_Command() = default;

	Audio_SetSoundVolume_Command(Sound::ID sound_id, Sound* pSound, float val);

	virtual void Execute() override;

public:
	// Data
	Sound::ID sound_id;
	Sound* pSound;
	float value;
};



#endif // !AUDIO_SETSOUNDVOLUME_COMMAND_H
// --- End of File ---
