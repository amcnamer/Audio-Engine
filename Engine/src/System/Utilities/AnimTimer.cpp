//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "AnimTimer.h"

AnimTimer::AnimTimer()
	: Azul::AnimTimer()
{

}

AnimTimer::~AnimTimer()
{

}

void AnimTimer::Tic()
{
	this->Azul::AnimTimer::Tic();
}

const AnimTime AnimTimer::Toc() const
{
	const Azul::AnimTime t = this->Azul::AnimTimer::Toc();

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	const AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}

//---  End of File ---
