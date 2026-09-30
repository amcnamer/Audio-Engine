
#ifndef FILE_ASYNC_LOAD_FILE_COMMAND_H
#define FILE_ASYNC_LOAD_FILE_COMMAND_H

#include "Command.h"
#include "Wave.h"

class File_AsyncLoadFile_Command : public Command
{
public:
	// Big 4
	File_AsyncLoadFile_Command() = delete;
	File_AsyncLoadFile_Command(const File_AsyncLoadFile_Command&) = delete;
	File_AsyncLoadFile_Command& operator = (const File_AsyncLoadFile_Command&) = delete;
	~File_AsyncLoadFile_Command();

	File_AsyncLoadFile_Command(Wave::ID id, const char* const pWaveName, Wave* pWave);

	virtual void Execute() override;

public:
	// Data
	Wave::ID wave_id;
	const char* const pWaveName;
	Wave* pWave;
};

#endif

// --- End of File ---
