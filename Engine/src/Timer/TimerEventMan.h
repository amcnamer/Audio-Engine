
            
#ifndef TIMER_EVENT_MAN_H
#define TIMER_EVENT_MAN_H 

#include "ManBase.h"
#include "DLinkMan.h"
#include "TimerEvent.h"
#include "AnimTimer.h"

class TimerEventMan : public ManBase
{

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
private:
    TimerEventMan(int reserveNum = 3, int reserveGrow = 1);
    ~TimerEventMan();

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
public:
    static void Create(int reserveNum = 3, int reserveGrow = 1);
    static void Destroy();

    static TimerEvent* Add(Command* pCommand, Azul::AnimTime deltaTimeToTrigger);
    static TimerEvent* Find(TimerEvent::ID id);
    static Azul::AnimTime GetTimeCurrent();

    static void Update();
    static void UpdateTimeOnly();
    static void Reset();

    static void Remove(TimerEvent* pNode);
    static void Dump();

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
private:
    static TimerEventMan* GetInstance();

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
protected:
    DLink* derivedCreateNode() override;


    //----------------------------------------------------------------------
    // Data: unique data for this manager 
    //----------------------------------------------------------------------
private:
    TimerEvent* poNodeCompare;
    static TimerEventMan* pInstance;

    Azul::AnimTime		mCurrTime;
    Azul::AnimTimer		GameTime;

};


#endif