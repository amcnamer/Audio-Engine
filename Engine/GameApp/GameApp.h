//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef GAME_APP_H
#define GAME_APP_H

using namespace Azul;

class Camera;
class Game;

class GameApp
{
public:
	static const unsigned int MAJOR_VERSION = 10;
	static const unsigned int MINOR_VERSION = 0;

public:
	static void LoadDemo(Game *pGame);
	static void UpdateDemo();
	static void DrawDemo();
	static void ClearDemo();
	static void UnloadDemo();

	GameApp();
	GameApp(const GameApp &) = delete;
	GameApp &operator = (const GameApp &) = delete;
	~GameApp();

	void SetDefaultTargetMode();
	float GetAspectRatio() const;

private:
	static GameApp *privGameApp();
	static GameApp *pInstance;

	Camera *pHackCamera;
	Game *pGame;
};


#endif

//---  End of File ---
