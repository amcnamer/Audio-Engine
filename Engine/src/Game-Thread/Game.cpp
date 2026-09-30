//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "Game.h"
#include "GameApp.h"
#include "Input.h"
#include "AudioThread.h"
#include "CircularData.h"
#include "SoundManager.h"
#include "Sound.h"
#include "HandleMan.h"
#include "AnimTimer.h"
#include "Audio_LoadWave_Command.h"
#include "PlaylistMan.h"
#include "PlaylistJukeBox.h"
#include "WaveMan.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "VoiceCallBack_One.h"
#include "VoiceCallBack_Two.h"
#include "VoiceCallBack_Stitched.h"
#include "Playlist_OneVoice_Command.h"
#include "Playlist_TwoVoice_Command.h"
#include "Audio.h"
#include "QueueMan.h"
#include "TimerMan.h"
#include "InputProcess.h"
#include "TimerEventMan.h"

// Needs to be an atomic
std::atomic_bool QuitFlag = false;
std::atomic_bool AudioReadyFlag = false;

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
bool Game::LoadContent()
{
	GameApp::LoadDemo(this);
	HandleMan::Create();
	SoundManager::Create();
	Audio::Create();
	QueueMan::Create();
	TimerMan::Create();
	TimerEventMan::Create();

	//---------------------------------
	// Launch a Thread
	//---------------------------------

	// Spawn Audio thread
	std::thread  t_Audio(Audio_Main, std::ref(QuitFlag), std::ref(AudioReadyFlag));
	Debug::SetName(t_Audio, "--Audio--");
	t_Audio.detach();

	// Wait until audio thread is ready.
	while (!AudioReadyFlag);
	return true;
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------

void Game::Update(float)
{
	// Update the demo application
	GameApp::UpdateDemo();

	TimerMan::Update();

	SoundManager::Update();

	TimerEventMan::Update();

	InputProcess();
	
	this->QuitCheck();
}

//-----------------------------------------------------------------------------
// Game::Render()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Render()
{
	GameApp::DrawDemo();}

//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnloadContent()
{
	GameApp::UnloadDemo();
	TimerEventMan::Destroy();
	TimerMan::Destroy();
	QueueMan::Destroy();
	Audio::Destroy();
	SoundManager::Destroy();
	HandleMan::Destroy();
}

//------------------------------------------------------------------
// Game::ClearBufferFunc()
// Clear the color and depth buffers.
//------------------------------------------------------------------
void Game::ClearDepthStencilBuffer()
{
	GameApp::ClearDemo();
}

void Game::QuitCheck()
{
	if (Input::GetKeyPress(KeyBoard::Key_Q))
	{
		QuitFlag = true;
	}
}

// --- End of File ---
