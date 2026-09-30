

#include "File_LoadFile_Command.h"
#include "Audio_FileLoadCompleted_Command.h"
#include "QueueMan.h"

File_LoadFile_Command::File_LoadFile_Command(Wave::ID id, const char* const _pWaveName, Wave* _pWave)
	: Command(),
	wave_id(id),
	pWaveName(_pWaveName),
	pWave(_pWave)
{
	assert(pWaveName);
	assert(pWave);
}

File_LoadFile_Command::~File_LoadFile_Command()
{

}

// From Audio --> File to execute
void File_LoadFile_Command::Execute()
{
	// Load the file and fill in the data structure
	// This will block on File Thread doing the loading.
	Audio_FileLoadCompleted_Command* pCmd = new Audio_FileLoadCompleted_Command(this->pWaveName, this->pWave);
	assert(pCmd);

	// Send the data to the Audio thread to register
	bool status = QueueMan::SendAudio(pCmd);
	assert(status == true);

	delete this;
}


// --- End of File ---
