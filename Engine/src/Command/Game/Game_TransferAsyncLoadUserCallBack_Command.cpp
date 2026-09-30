

#include "Game_TransferAsyncLoadUserCallBack_Command.h"
#include "WaveMan.h"
#include "StringEnum.h"


Game_TransferAsyncLoadUserCallBack_Command::Game_TransferAsyncLoadUserCallBack_Command(
	UserAsyncLoadCallBack* _pUserAsyncLoadCallback)
	: Command(),
	pUserAsyncLoadCallback(_pUserAsyncLoadCallback)
{

}

void Game_TransferAsyncLoadUserCallBack_Command::Execute()
{
	Debug::out("Game_TransferAsyncLoadUserCallback_Cmd::Execute(%s)\n",
		StringMe(this->pUserAsyncLoadCallback->GetWaveID()));

	if (this->pUserAsyncLoadCallback != nullptr)
	{
		this->pUserAsyncLoadCallback->Execute();
		delete this->pUserAsyncLoadCallback;
	}

	delete this;
}
