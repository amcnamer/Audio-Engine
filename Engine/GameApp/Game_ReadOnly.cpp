//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "Game.h"
#include "File.h"
#include "GameApp.h"

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

Game::Game(const char *const pName, int width, int height)
	: Engine(pName, width, height)
{

	unsigned int magic;
	File::Error ferror;
	ferror = File::Magic(magic);
	assert(ferror == File::Error::SUCCESS);
	assert(magic == 0xA1B1);

	assert(GameApp::MAJOR_VERSION == 10);
	assert(GameApp::MINOR_VERSION == 0);
}

Game::~Game()
{
}

// --- End of File ---
