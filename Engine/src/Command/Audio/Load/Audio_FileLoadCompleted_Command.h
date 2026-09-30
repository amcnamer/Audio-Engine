
#ifndef AUDIO_FILE_LOAD_COMPLETED_COMMAND_H
#define AUDIO_FILE_LOAD_COMPLETED_COMMAND_H

#include "Wave.h"
#include "Command.h"

struct Audio_FileLoadCompleted_Command : public Command
{
	Audio_FileLoadCompleted_Command() = delete;
	Audio_FileLoadCompleted_Command(const Audio_FileLoadCompleted_Command&) = delete;
	Audio_FileLoadCompleted_Command& operator = (const Audio_FileLoadCompleted_Command&) = delete;
	~Audio_FileLoadCompleted_Command() = default;

	Audio_FileLoadCompleted_Command(const char* const pWaveName, Wave* pWave);
	void LoadBuffer(const char* const pWaveName);

	void Execute() override;

	WAVEFORMATEXTENSIBLE* pWfx;
	RawData* pRawBuff;
	unsigned long           rawBuffSize;
	Wave* pWave;
};

#endif