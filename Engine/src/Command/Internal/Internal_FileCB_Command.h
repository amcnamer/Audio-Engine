
#ifndef INTERNAL_FILE_CB_CMD_H
#define INTERNAL_FILE_CB_CMD_H

class Internal_FileCB_Command
{
public:
	Internal_FileCB_Command(bool& DoneFlag);
	Internal_FileCB_Command(const Internal_FileCB_Command&) = delete;
	Internal_FileCB_Command& operator = (const Internal_FileCB_Command&) = delete;
	~Internal_FileCB_Command() = default;

	void Execute();

private:
	bool& rDoneFlag;
};

#endif