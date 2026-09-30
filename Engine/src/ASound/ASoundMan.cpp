
#include "ASoundMan.h"
#include "SoundManager.h"

ASoundMan* ASoundMan::pInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
ASoundMan::ASoundMan(int reserveNum, int reserveGrow)
	: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
	// Preload the reserve
	this->proFillReservedPool(reserveNum);

	// initialize derived data here
	this->poNodeCompare = new ASound();
}

ASoundMan::~ASoundMan()
{
	// Debug::out("~ASnd()\n");
	delete this->poNodeCompare;
	this->poNodeCompare = nullptr;

	// iterate through the list and delete
	Iterator* pIt = this->baseGetActiveIterator();

	DLink* pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		ASound* pDeleteMe = (ASound*)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}

	pIt = this->baseGetReserveIterator();

	pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		ASound* pDeleteMe = (ASound*)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void ASoundMan::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new ASoundMan(reserveNum, reserveGrow);
	}

}

void ASoundMan::Destroy()
{
	ASoundMan* pMan = ASoundMan::GetInstance();
	assert(pMan != nullptr);

	delete ASoundMan::pInstance;
	ASoundMan::pInstance = nullptr;
}

ASound* ASoundMan::Add(Sound::ID snd_id, Sound* pSnd)
{
	ASoundMan* pMan = ASoundMan::GetInstance();

	ASound* pNode = (ASound*)pMan->baseAddToFront();
	assert(pNode != nullptr);

	// Initialize the date
	assert(pSnd);
	pNode->Set(snd_id, pSnd);

	return pNode;
}

ASound* ASoundMan::Find(Sound::ID _id)
{
	ASoundMan* pMan = ASoundMan::GetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->sound_id = _id;

	ASound* pData = (ASound*)pMan->baseFind(pMan->poNodeCompare);
	return pData;
}

void ASoundMan::Remove(ASound* pNode)
{
	assert(pNode != nullptr);

	ASoundMan* pMan = ASoundMan::GetInstance();
	assert(pMan != nullptr);

	pMan->baseRemove(pNode);
}

void ASoundMan::Dump()
{
	ASoundMan* pMan = ASoundMan::GetInstance();
	assert(pMan != nullptr);

	pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
ASoundMan* ASoundMan::GetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* ASoundMan::derivedCreateNode()
{
	DLink* pNodeBase = new ASound();
	assert(pNodeBase != nullptr);

	return pNodeBase;
}

