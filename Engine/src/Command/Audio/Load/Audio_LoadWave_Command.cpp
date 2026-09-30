//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Audio_LoadWave_Command.h"
#include "WaveMan.h"

Audio_LoadWave_Command::Audio_LoadWave_Command(Wave::ID _id, const char* const _pWaveName, Internal_FileCB_Command *_pFileCB)
	: Command(),
	id(_id),
	pWaveName(_pWaveName),
	pIFileCB(_pFileCB)
{
	assert(pWaveName);
}


void Audio_LoadWave_Command::Execute()
{
	WaveMan::Add(this->id, this->pWaveName, this->pIFileCB);

	delete this;
}


// --- End of File ---
