
#include "QueueMan.h"
#include "Command.h"

void Aux_Main(std::atomic_bool& QuitFlag)
{
	SimpleBanner b;

	CircularData* pAuxIn = QueueMan::GetAuxInQueue();

	// ----------------------------------------
	// Loop for ever until quit is hit
	// ----------------------------------------
	while (!QuitFlag)
	{
		Command* pCmd;

		if (pAuxIn->PopFront(pCmd) == true)
		{
			assert(pCmd);
			pCmd->Execute();
		}
	}
}