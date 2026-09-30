
#include "Internal_FileCB_Command.h"

Internal_FileCB_Command::Internal_FileCB_Command(bool& DoneFlag)
	: rDoneFlag(DoneFlag)
{

}

void Internal_FileCB_Command::Execute()
{
	//Debug::out("Internal_FileCB_Cmd()::Execute()\n");

	this->rDoneFlag = true;

	delete this;
}