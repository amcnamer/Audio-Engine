//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef AUDIO_THREAD_H
#define AUDIO_THREAD_H

#include "CircularData.h"

void Audio_Main(std::atomic_bool& QuitFlag, std::atomic_bool &AudioReadyFlag);

#endif

//---  End of File ---
