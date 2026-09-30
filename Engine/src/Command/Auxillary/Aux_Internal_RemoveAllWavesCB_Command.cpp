

#include "Aux_Internal_RemoveAllWavesCB_Command.h"

Aux_Internal_RemoveAllWavesCB_Command::Aux_Internal_RemoveAllWavesCB_Command(Internal_FileCB_Command* _pIFileCB)
	: pIFileCB(_pIFileCB)
{
	assert(pIFileCB);
}

void Aux_Internal_RemoveAllWavesCB_Command::Execute()
{
	Debug::out("Aux_Internal_RemoveAllWavesCB_Command::Execute()\n");

	this->pIFileCB->Execute();

	delete this;
}
