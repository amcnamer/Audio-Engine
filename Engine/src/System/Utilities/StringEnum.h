//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef STRING_ENUM_H
#define STRING_ENUM_H

#include "Handle.h"
#include "Voice.h"
#include "Wave.h"
#include "Sound.h"
#include "WaveTable.h"

class StringEnum
{
public:
	static const unsigned int BUFFER_SIZE = 64;
public:
	StringEnum(Handle::Status status);
	StringEnum(Wave::ID id);
	StringEnum(Sound::ID id);
	StringEnum(Wave::Status id);

	operator char* ();

	// data:
	char buffer[BUFFER_SIZE];
};

#define StringMe(x)  ((char *)StringEnum(x)) 

#endif

// --- End of File ---
