
#ifndef DEMO_H
#define DEMO_H

#include "AnimTime.h"

class Demo
{
public:
	Demo(Azul::AnimTime time);

	Demo() = delete;
	Demo(const Demo&) = delete;
	Demo& operator = (const Demo&) = delete;
	virtual ~Demo() = default;

	virtual void Load() = 0;
	virtual void Execute() = 0;

	Azul::AnimTime startTime;
};

#endif