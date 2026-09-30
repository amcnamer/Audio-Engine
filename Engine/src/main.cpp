//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "Game.h"
#include "google\protobuf\message_lite.h"
#include "File.h"

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	START_BANNER_MAIN("--Main--");

	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	Game *poGame = new Game("CSC588 13.0.12.9.5", 2*200, 2*150);

	//set location for reference audio files
	File::SetBaseDir("..\\..\\..\\..\\reference\\AudioFiles\\");

	// launch game
	poGame->wWinMain(hInstance, prevInstance, cmdLine, cmdShow);

	delete poGame;

	// clean shut down
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

// --- End of File ---
