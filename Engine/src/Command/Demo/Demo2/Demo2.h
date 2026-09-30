
#include "Demo.h"

class Demo2 : public Demo
{
public:
	Demo2(Azul::AnimTime time);
	Demo2() = delete;
	Demo2(const Demo2&) = delete;
	Demo2& operator=(const Demo2&) = delete;
	virtual ~Demo2();

	virtual void Load() override;
	virtual void Execute() override;
};