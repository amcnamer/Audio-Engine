
#ifndef AUX_FILE_CB_COMMAND_H
#define AUX_FILE_CB_COMMAND_H

#include "Command.h"
#include "Internal_FileCB_Command.h"

struct Aux_FileCB_Command : public Command
{
	Aux_FileCB_Command() = delete;
	Aux_FileCB_Command(const Aux_FileCB_Command&) = delete;
	Aux_FileCB_Command& operator = (const Aux_FileCB_Command&) = delete;
	~Aux_FileCB_Command() = default;

	Aux_FileCB_Command(Internal_FileCB_Command* pIFileCB);

	void Execute() override;


	Internal_FileCB_Command* pIFileCB;
};

#endif