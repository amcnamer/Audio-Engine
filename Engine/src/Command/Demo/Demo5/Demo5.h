
#include "Demo.h"

class Demo5 : public Demo
{
public:
	Demo5(Azul::AnimTime time);
	Demo5() = delete;
	Demo5(const Demo5&) = delete;
	Demo5& operator=(const Demo5&) = delete;
	virtual ~Demo5();

	virtual void Load() override;
	virtual void Execute() override;
};