
#include "TimerEventMan.h"

TimerEventMan* TimerEventMan::pInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
TimerEventMan::TimerEventMan(int reserveNum, int reserveGrow)
    : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
    // Preload the reserve
    this->proFillReservedPool(reserveNum);

    // initialize derived data here
    this->poNodeCompare = new TimerEvent();

    this->GameTime.Tic();
    this->mCurrTime = this->GameTime.Toc();
}

TimerEventMan::~TimerEventMan()
{
    // Debug::out("~WaveMan()\n");
    delete this->poNodeCompare;
    this->poNodeCompare = nullptr;

    // iterate through the list and delete
    Iterator* pIt = this->baseGetActiveIterator();

    DLink* pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        TimerEvent* pDelete = (TimerEvent*)pIt->Curr();
        pNode = pIt->Next();
        delete pDelete;
    }

    pIt = this->baseGetReserveIterator();

    pNode = pIt->First();

    // Walk through the nodes
    while (!pIt->IsDone())
    {
        TimerEvent* pDelete = (TimerEvent*)pIt->Curr();
        pNode = pIt->Next();
        delete pDelete;
    }
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void TimerEventMan::Create(int reserveNum, int reserveGrow)
{
    // Do the initialization
    if (pInstance == nullptr)
    {
        pInstance = new TimerEventMan(reserveNum, reserveGrow);
    }

}

void TimerEventMan::Destroy()
{
    TimerEventMan* pMan = TimerEventMan::GetInstance();
    assert(pMan != nullptr);

    delete TimerEventMan::pInstance;
    TimerEventMan::pInstance = nullptr;
}

void TimerEventMan::Reset()
{
    // Get the instance
    TimerEventMan* pMan = TimerEventMan::GetInstance();
    assert(pMan);

    pMan->GameTime.Tic();
    pMan->mCurrTime = pMan->GameTime.Toc();
}

void TimerEventMan::UpdateTimeOnly()
{
    // Get the instance
    TimerEventMan* pMan = TimerEventMan::GetInstance();
    assert(pMan);

    pMan->mCurrTime = pMan->GameTime.Toc();
}

void TimerEventMan::Update()
{
    // Get the instance
    TimerEventMan* pMan = TimerEventMan::GetInstance();
    assert(pMan);

    // squirrel away
    pMan->mCurrTime = pMan->GameTime.Toc();

    // iterate through the list and delete
    Iterator* pIt = pMan->baseGetActiveIterator();

    // Walk through the nodes
    DLink* pNode = pIt->First();

    while (!pIt->IsDone())
    {
        TimerEvent* pTimeEvent = (TimerEvent*)pNode;
        pNode = pIt->Next();

        if (pMan->mCurrTime >= (pTimeEvent->GetTriggerTime()))
        {
            // call it
            pTimeEvent->Process();

            // remove from list
            pMan->baseRemove(pTimeEvent);
        }

    }
}


TimerEvent* TimerEventMan::Add(Command* pCommand, Azul::AnimTime deltaTimeToTrigger)
{
    TimerEventMan* pMan = TimerEventMan::GetInstance();
    assert(pMan != nullptr);

    TimerEvent* pNode = (TimerEvent*)pMan->baseAddToFront();
    assert(pNode != nullptr);

    // Create a new one given a wash
    assert(pCommand);
    pNode->Set(pCommand, deltaTimeToTrigger);

    return pNode;
}

TimerEvent* TimerEventMan::Find(TimerEvent::ID _id)
{
    TimerEventMan* pMan = TimerEventMan::GetInstance();
    assert(pMan != nullptr);

    // Compare functions only compares two Nodes

    // So:  Use the Compare Node - as a reference
    //      use in the Compare() function
    pMan->poNodeCompare->SetID(_id);

    TimerEvent* pData = (TimerEvent*)pMan->baseFind(pMan->poNodeCompare);
    return pData;
}

void TimerEventMan::Remove(TimerEvent* pNode)
{
    assert(pNode != nullptr);

    TimerEventMan* pMan = TimerEventMan::GetInstance();
    assert(pMan != nullptr);

    pMan->baseRemove(pNode);
}

void TimerEventMan::Dump()
{
    TimerEventMan* pMan = TimerEventMan::GetInstance();
    assert(pMan != nullptr);

    pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
TimerEventMan* TimerEventMan::GetInstance()
{
    return pInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* TimerEventMan::derivedCreateNode()
{
    DLink* pNodeBase = new TimerEvent();
    assert(pNodeBase != nullptr);

    return pNodeBase;
}

Azul::AnimTime TimerEventMan::GetTimeCurrent()
{
    // Get the instance
    TimerEventMan* pMan = TimerEventMan::GetInstance();
    assert(pMan != nullptr);

    return pMan->mCurrTime;
}

// --- End of File ---
