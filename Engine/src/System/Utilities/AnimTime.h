//----------------------------------------------------------------------------- 
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef ANIM_TIME_WRAPPER_H
#define ANIM_TIME_WRAPPER_H

#include "include\AnimTime.h"

class AnimTime : public Azul::AnimTime
{
public:

	enum class Duration
	{
		// For constructing a AnimTime of zero. 
		ZERO,

		// For constructing one NTSC 60 hz frame of AnimTime.
		NTSC_FRAME,

		// For constructing one NTSC 60 hz frame of AnimTime. 
		NTSC_30_FRAME,

		// 24 Hz frames per second
		FILM_24_FRAME,

		// For constructing one PAL 50 hz frame of AnimTime. 
		PAL_FRAME,

		// For constructing one microsecond of AnimTime. 
		ONE_MICROSECOND,

		// For constructing one millisecond of AnimTime. 
		ONE_MILLISECOND,

		// For constructing one second of AnimTime. 
		ONE_SECOND,

		// For constructing one minute of AnimTime. 
		ONE_MINUTE,

		// For constructing one hour of AnimTime. 
		ONE_HOUR,

		// For constructing the most _negative_ AnimTime that can be represented.
		MIN,

		// For constructing the most positive AnimTime that can be represented.
		MAX,

		// insure the enum is size int
		DWORD = 0x7FFFFFFF
	};

public:

	//-----------------------------------------------------------------
	// Friends
	//-----------------------------------------------------------------

	friend const AnimTime operator*(const float, const AnimTime&);
	friend const AnimTime operator*(const int, const AnimTime&);

	//-----------------------------------------------------------------
	// Constructors / Destructors / Assignment
	//-----------------------------------------------------------------


	AnimTime();
	explicit AnimTime(const Duration);
	AnimTime(const AnimTime&);
	AnimTime& operator=(const AnimTime& rhs);
	~AnimTime();

	//-----------------------------------------------------------------
	// Comparisons
	//-----------------------------------------------------------------

	bool operator==(const AnimTime& rhs) const;
	bool operator!=(const AnimTime& rhs) const;
	bool operator<(const AnimTime& rhs) const;
	bool operator<=(const AnimTime& rhs) const;
	bool operator>(const AnimTime& rhs) const;
	bool operator>=(const AnimTime& rhs) const;

	//-----------------------------------------------------------------
	// Negation / Addition / Subtraction
	//-----------------------------------------------------------------

	const AnimTime operator-() const;
	const AnimTime operator+(const AnimTime& rhs) const;
	const AnimTime operator-(const AnimTime& rhs) const;
	AnimTime& operator+=(const AnimTime& rhs);
	AnimTime& operator-=(const AnimTime& rhs);

	//-----------------------------------------------------------------
	// Multiplication
	//-----------------------------------------------------------------

	const AnimTime operator*(const float) const;
	const AnimTime operator*(const int) const;
	AnimTime& operator*=(const float);
	AnimTime& operator*=(const int);

	//-----------------------------------------------------------------
	// name: Division
	//-----------------------------------------------------------------

	float operator/(const AnimTime& denominator) const;
	const AnimTime operator/(const float denominator) const;
	const AnimTime operator/(const int denominator) const;
	AnimTime& operator/=(const float);
	AnimTime& operator/=(const int);

	//-----------------------------------------------------------------
	// Quotient / Remainder
	//-----------------------------------------------------------------

	static int 	Quotient(const AnimTime& numerator, const AnimTime& denominator);
	//static const AnimTime 	Remainder(const AnimTime& numerator, const AnimTime& denominator);

};

#endif

//---  End of File ---