
#include "Aux_FileCB_Command.h"

Aux_FileCB_Command::Aux_FileCB_Command(Internal_FileCB_Command* _pIFileCB)
	: pIFileCB(_pIFileCB)
{
	assert(pIFileCB);
}

void Aux_FileCB_Command::Execute()
{
	//Debug::out("Aux_FileCB_Cmd::Execute()\n");

	this->pIFileCB->Execute();

	delete this;
}