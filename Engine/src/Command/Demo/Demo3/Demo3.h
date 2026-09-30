#ifndef DEMO_3_H
#define DEMO_3_H

#include "Demo.h"

class Demo3 : public Demo
{
public:
	Demo3(Azul::AnimTime time);

	Demo3() = delete;
	Demo3(const Demo3&) = delete;
	Demo3& operator = (const Demo3&) = delete;
	virtual ~Demo3();

	virtual void Load() override;
	virtual void Execute() override;
};

#endif
