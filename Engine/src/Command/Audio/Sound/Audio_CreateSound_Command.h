
#ifndef AUDIO_CREATESOUND_COMMAND_H
#define AUDIO_CREATESOUND_COMMAND_H

#include "Command.h"
#include "Sound.h"

class Audio_CreateSound_Command : public Command
{

public:
	// Big 4
	Audio_CreateSound_Command() = delete;
	Audio_CreateSound_Command(const Audio_CreateSound_Command&) = delete;
	Audio_CreateSound_Command& operator = (const Audio_CreateSound_Command&) = delete;
	~Audio_CreateSound_Command() = default;

	Audio_CreateSound_Command(Sound::ID sound_id, Sound* pSound, UserSoundCallBack* pUserSoundCallback);

	virtual void Execute() override;

public:
	// Data
	Sound::ID sound_id;
	Sound* pSound;
	UserSoundCallBack* pUserSoundCallback;
};

#endif
