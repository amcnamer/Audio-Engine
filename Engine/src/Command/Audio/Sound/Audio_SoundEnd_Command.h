
#ifndef AUDIO_SOUNDEND_COMMAND_H
#define AUDIO_SOUNDEND_COMMAND_H

#include "Command.h"
#include "Sound.h"

class Audio_SoundEnd_Command : public Command
{

public:
	// Big 4
	Audio_SoundEnd_Command() = delete;
	Audio_SoundEnd_Command(const Audio_SoundEnd_Command&) = delete;
	Audio_SoundEnd_Command& operator = (const Audio_SoundEnd_Command&) = delete;
	~Audio_SoundEnd_Command() = default;

	Audio_SoundEnd_Command(Sound::ID sound_id, Sound* pSound);

	virtual void Execute() override;

public:
	// Data
	Sound::ID sound_id;
	Sound* pSound;
};

#endif