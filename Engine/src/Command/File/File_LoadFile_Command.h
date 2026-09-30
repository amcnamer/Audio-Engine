#ifndef FILE_FILE_LOAD_COMMAND_H
#define FILE_FILE_LOAD_COMMAND_H

#include "Command.h"
#include "Wave.h"

class File_LoadFile_Command : public Command
{
public:
	// Big 4
	File_LoadFile_Command() = delete;
	File_LoadFile_Command(const File_LoadFile_Command&) = delete;
	File_LoadFile_Command& operator = (const File_LoadFile_Command&) = delete;
	~File_LoadFile_Command();

	File_LoadFile_Command(Wave::ID id, const char* const pWaveName, Wave* pWave);

	virtual void Execute() override;

public:
	// Data
	Wave::ID wave_id;
	const char* const pWaveName;
	Wave* pWave;
};

#endif