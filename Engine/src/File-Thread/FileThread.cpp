#include "QueueMan.h"
#include "Command.h"

void File_Main(std::atomic_bool& QuitFlag)
{
	SimpleBanner b;

	CircularData* pFileIn = QueueMan::GetFileInQueue();

	// ----------------------------------------
	// Loop for ever until quit is hit
	// ----------------------------------------
	while (!QuitFlag)
	{
		Command* pCmd;

		if (pFileIn->PopFront(pCmd) == true)
		{
			assert(pCmd);
			pCmd->Execute();
		}
	}

}