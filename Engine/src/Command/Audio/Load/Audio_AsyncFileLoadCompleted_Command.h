

#ifndef AUDIO_ASYNC_FILE_LOAD_COMPLETED_COMMAND_H
#define AUDIO_ASYNC_FILE_LOAD_COMPLETED_COMMAND_H

#include "Wave.h"
#include "Command.h"

struct Audio_AsyncFileLoadCompleted_Command: public Command
{
	Audio_AsyncFileLoadCompleted_Command() = delete;
	Audio_AsyncFileLoadCompleted_Command(const Audio_AsyncFileLoadCompleted_Command&) = delete;
	Audio_AsyncFileLoadCompleted_Command& operator = (const Audio_AsyncFileLoadCompleted_Command&) = delete;
	~Audio_AsyncFileLoadCompleted_Command() = default;

	Audio_AsyncFileLoadCompleted_Command(const char* const pWaveName, Wave* pWave);
	void LoadBuffer(const char* const pWaveName);

	void Execute() override;

	WAVEFORMATEXTENSIBLE* poWfx;
	RawData* poRawBuff;
	unsigned long           rawBuffSize;
	Wave* pWave;
};

#endif

//---  End of File ---

