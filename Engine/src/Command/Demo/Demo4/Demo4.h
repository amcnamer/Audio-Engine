#ifndef DEMO_4_H
#define DEMO_4_H

#include "Demo.h"

class Demo4 : public Demo
{
public:
	Demo4(Azul::AnimTime time);

	Demo4() = delete;
	Demo4(const Demo4&) = delete;
	Demo4& operator = (const Demo4&) = delete;
	virtual ~Demo4();

	virtual void Load() override;
	virtual void Execute() override;
};

#endif