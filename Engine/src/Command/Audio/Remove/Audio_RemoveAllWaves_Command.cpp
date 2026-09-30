

#include "Audio_RemoveAllWaves_Command.h"
#include "WaveMan.h"
#include "StringEnum.h"

Audio_RemoveAllWaves_Command::Audio_RemoveAllWaves_Command(Internal_FileCB_Command* _pFileCB)
	: Command(),
	pIFileCB(_pFileCB)
{
	assert(pIFileCB);
}

void Audio_RemoveAllWaves_Command::Execute()
{
	Debug::out("Audio_RemoveAllWaves_Command::Execute()\n");

	WaveMan::RemoveAll(this->pIFileCB);

	delete this;
}
