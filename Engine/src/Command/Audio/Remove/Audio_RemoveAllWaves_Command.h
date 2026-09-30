

#ifndef AUDIO_REMOVE_ALL_WAVES_COMMAND_H
#define AUDIO_REMOVE_ALL_WAVES_COMMAND_H

#include "Command.h"
#include "Wave.h"
#include "Internal_FileCB_Command.h"

class Audio_RemoveAllWaves_Command : public Command
{
public:
	// Big 4
	Audio_RemoveAllWaves_Command() = delete;
	Audio_RemoveAllWaves_Command(const Audio_RemoveAllWaves_Command&) = delete;
	Audio_RemoveAllWaves_Command& operator = (const Audio_RemoveAllWaves_Command&) = delete;
	~Audio_RemoveAllWaves_Command() = default;

	Audio_RemoveAllWaves_Command(Internal_FileCB_Command* pFileCB);

	virtual void Execute() override;

public:
	// Data
	Wave::ID id;
	Internal_FileCB_Command* pIFileCB;
};

#endif
