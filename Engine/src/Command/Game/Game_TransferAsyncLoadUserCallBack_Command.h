

#ifndef GAME_TRANSFER_ASYNC_LOAD_USER_CALLBACK_COMMAND_H
#define GAME_TRANSFER_ASYNC_LOAD_USER_CALLBACK_COMMAND_H

#include "Command.h"
#include "UserAsyncLoadCallBack.h"

class Game_TransferAsyncLoadUserCallBack_Command : public Command
{
public:
	// Big 4
	Game_TransferAsyncLoadUserCallBack_Command() = delete;
	Game_TransferAsyncLoadUserCallBack_Command(const Game_TransferAsyncLoadUserCallBack_Command&) = delete;
	Game_TransferAsyncLoadUserCallBack_Command& operator = (const Game_TransferAsyncLoadUserCallBack_Command&) = delete;
	~Game_TransferAsyncLoadUserCallBack_Command() = default;

	Game_TransferAsyncLoadUserCallBack_Command(UserAsyncLoadCallBack* pUserAsyncLoadCallback);

	virtual void Execute() override;

public:
	// Data
	UserAsyncLoadCallBack* pUserAsyncLoadCallback;
};

#endif

// --- End of File ---
