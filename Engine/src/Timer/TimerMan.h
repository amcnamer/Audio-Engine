
#ifndef TIMER_MAN_H
#define TIMER_MAN_H

#include "AnimTimer.h"

class TimerMan
{
public:
	static void Create();
	static void Destroy();

	static void Update();
	static Azul::AnimTime GetTimeCurrent();

private:
	TimerMan();
	TimerMan(const TimerMan&) = delete;
	TimerMan& operator = (const TimerMan&) = delete;
	~TimerMan();

	static TimerMan* GetInstance();
	static TimerMan* pInstance;

	Azul::AnimTimer mGameTimer;
	Azul::AnimTime  mCurrTime;

};

#endif
