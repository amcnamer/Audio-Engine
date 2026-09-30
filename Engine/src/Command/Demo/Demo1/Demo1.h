
#include "Demo.h"

class Demo1 : public Demo
{
public:
	Demo1(Azul::AnimTime time);
	Demo1() = delete;
	Demo1(const Demo1&) = delete;
	Demo1& operator=(const Demo1&) = delete;
	virtual ~Demo1();

	virtual void Load() override;
	virtual void Execute() override;
};