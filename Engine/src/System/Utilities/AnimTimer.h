//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef ANIM_TIMER_WRAPPER_H
#define ANIM_TIMER_WRAPPER_H

#include "AnimTime.h"
#include "include\AnimTimer.h"

class AnimTimer : public Azul::AnimTimer
{
public:

	//-----------------------------------------------------------------
	// Constructors / Destructors
	//-----------------------------------------------------------------

	AnimTimer();
	AnimTimer(const AnimTimer&) = delete;
	AnimTimer& operator = (const AnimTimer&) = delete;
	~AnimTimer();

	//-----------------------------------------------------------------
	// Timing Methods
	//-----------------------------------------------------------------

	void Tic();
	const AnimTime Toc() const;

};

#endif

//---  End of File ---
