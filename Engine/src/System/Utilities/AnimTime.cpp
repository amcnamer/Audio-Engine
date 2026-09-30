//----------------------------------------------------------------------------- 
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "AnimTime.h"

//-----------------------------------------------------------------
// Friends
//-----------------------------------------------------------------

const AnimTime operator*(const float s, const AnimTime& r)
{
	Azul::AnimTime t = s * (Azul::AnimTime)r;

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	const AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}

const AnimTime operator*(const int s, const AnimTime& r)
{
	Azul::AnimTime t = s * (Azul::AnimTime)r;

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	const AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}

//-----------------------------------------------------------------
// Constructors / Destructors / Assignment
//-----------------------------------------------------------------


AnimTime::AnimTime()
{
}

AnimTime::AnimTime(const Duration d)
	: Azul::AnimTime((Azul::AnimTime::Duration)d)
{
}

AnimTime::AnimTime(const AnimTime& r)
	:Azul::AnimTime(r)
{
}

AnimTime& AnimTime::operator=(const AnimTime& rhs)
{
	Azul::AnimTime::operator=(rhs);
	return *this;
}

AnimTime::~AnimTime()
{
}

//-----------------------------------------------------------------
// Comparisons
//-----------------------------------------------------------------

bool AnimTime::operator==(const AnimTime& rhs) const
{
	return Azul::AnimTime::operator==(rhs);
}
bool AnimTime::operator!=(const AnimTime& rhs) const
{
	return Azul::AnimTime::operator!=(rhs);
}
bool AnimTime::operator<(const AnimTime& rhs) const
{
	return Azul::AnimTime::operator<(rhs);
}
bool AnimTime::operator<=(const AnimTime& rhs) const
{
	return Azul::AnimTime::operator<=(rhs);
}
bool AnimTime::operator>(const AnimTime& rhs) const
{
	return Azul::AnimTime::operator>(rhs);
}
bool AnimTime::operator>=(const AnimTime& rhs) const
{
	return Azul::AnimTime::operator>=(rhs);
}

//-----------------------------------------------------------------
// Negation / Addition / Subtraction
//-----------------------------------------------------------------

const AnimTime AnimTime::operator-() const
{
	const Azul::AnimTime t = Azul::AnimTime::operator-();

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	const AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}

const AnimTime AnimTime::operator+(const AnimTime& rhs) const
{
	const Azul::AnimTime t = Azul::AnimTime::operator+(rhs);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	const AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}

const AnimTime AnimTime::operator-(const AnimTime& rhs) const
{
	const Azul::AnimTime t = Azul::AnimTime::operator-(rhs);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	const AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}

AnimTime& AnimTime::operator+=(const AnimTime& rhs)
{
	const Azul::AnimTime& t = Azul::AnimTime::operator+=(rhs);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}

AnimTime& AnimTime::operator-=(const AnimTime& rhs)
{
	const Azul::AnimTime& t = Azul::AnimTime::operator-=(rhs);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}

//-----------------------------------------------------------------
// Multiplication
//-----------------------------------------------------------------

const AnimTime AnimTime::operator*(const float s) const
{
	const Azul::AnimTime t = Azul::AnimTime::operator*(s);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	const AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}
const AnimTime AnimTime::operator*(const int s) const
{
	const Azul::AnimTime t = Azul::AnimTime::operator*(s);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	const AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}
AnimTime& AnimTime::operator*=(const float s)
{
	const Azul::AnimTime& t = Azul::AnimTime::operator*=(s);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}
AnimTime& AnimTime::operator*=(const int s)
{
	const Azul::AnimTime& t = Azul::AnimTime::operator*=(s);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}

//-----------------------------------------------------------------
// name: Division
//-----------------------------------------------------------------

float AnimTime::operator/(const AnimTime& denominator) const
{
	return Azul::AnimTime::operator/(denominator);
}
const AnimTime AnimTime::operator/(const float denominator) const
{
	const Azul::AnimTime t = Azul::AnimTime::operator/(denominator);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	const AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}
const AnimTime AnimTime::operator/(const int denominator) const
{
	const Azul::AnimTime t = Azul::AnimTime::operator*(denominator);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	const AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}
AnimTime& AnimTime::operator/=(const float s)
{
	const Azul::AnimTime& t = Azul::AnimTime::operator/=(s);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}
AnimTime& AnimTime::operator/=(const int s)
{
	const Azul::AnimTime& t = Azul::AnimTime::operator/=(s);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}

//-----------------------------------------------------------------
// Quotient / Remainder
//-----------------------------------------------------------------

int AnimTime::Quotient(const AnimTime& numerator, const AnimTime& denominator)
{
	return Azul::AnimTime::Quotient(numerator, denominator);
}

const AnimTime Remainder(const AnimTime& numerator, const AnimTime& denominator)
{
	const Azul::AnimTime t = Azul::AnimTime::Remainder(numerator, denominator);

	// Wow - this was weird
	Azul::AnimTime* ptr = const_cast<Azul::AnimTime*>(&t);
	const AnimTime* p = reinterpret_cast<AnimTime*>(ptr);

	return *p;
}



//---  End of File ---