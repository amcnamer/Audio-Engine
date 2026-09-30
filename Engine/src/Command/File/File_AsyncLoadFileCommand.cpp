

#include "File_AsyncLoadFile_Command.h"
#include "Audio_AsyncFileLoadCompleted_Command.h"
#include "QueueMan.h"

File_AsyncLoadFile_Command::File_AsyncLoadFile_Command(Wave::ID id, const char* const _pWaveName, Wave* _pWave)
	: Command(),
	wave_id(id),
	pWaveName(_pWaveName),
	pWave(_pWave)
{
	assert(pWaveName);
	assert(pWave);
}

File_AsyncLoadFile_Command::~File_AsyncLoadFile_Command()
{

}

// From Audio --> File to execute
void File_AsyncLoadFile_Command::Execute()
{
	Debug::out("File_AsyncLoadFile_Cmd::Execute(%s)\n", this->pWaveName);

	// Load the file and fill in the data structure
	// This will block on File Thread doing the loading.
	Audio_AsyncFileLoadCompleted_Command* pCmd = new Audio_AsyncFileLoadCompleted_Command(this->pWaveName, this->pWave);
	assert(pCmd);

	// Send the data to the Audio thread to register
//	Debug::out("--> Audio_AsyncFileLoadCompleted_Cmd \n");
	bool status = QueueMan::SendAudio(pCmd);
	assert(status == true);

	delete this;
}


// --- End of File ---
