

#include "TimerMan.h"

TimerMan* TimerMan::pInstance = nullptr;

TimerMan::TimerMan()
{
	this->mGameTimer.Tic();
	this->mCurrTime = this->mGameTimer.Toc();
}

TimerMan::~TimerMan()
{

}

void TimerMan::Destroy()
{
	TimerMan* pTimerMan = TimerMan::GetInstance();
	assert(pTimerMan != nullptr);

	delete TimerMan::pInstance;
	TimerMan::pInstance = nullptr;
}

void TimerMan::Create()
{
	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new TimerMan();
	}
}

TimerMan* TimerMan::GetInstance()
{
	return pInstance;
}

void TimerMan::Update()
{
	TimerMan* pTimerMan = TimerMan::GetInstance();
	assert(pTimerMan != nullptr);

	pTimerMan->mCurrTime = pTimerMan->mGameTimer.Toc();
}

Azul::AnimTime TimerMan::GetTimeCurrent()
{
	TimerMan* pTimerMan = TimerMan::GetInstance();
	assert(pTimerMan != nullptr);

	return pTimerMan->mCurrTime;
}

