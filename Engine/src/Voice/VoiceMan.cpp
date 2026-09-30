

#include "VoiceMan.h"
#include "WaveMan.h"

VoiceMan* VoiceMan::pInstance = nullptr;

VoiceMan::VoiceMan(int reserveNum, int reserveGrow)
	: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
	this->proFillReservedPool(reserveNum);
	this->pNodeCompare = new Voice();
}

VoiceMan::~VoiceMan()
{
	delete this->pNodeCompare;
	this->pNodeCompare = nullptr;

	Iterator* pIt = this->baseGetActiveIterator();
	DLink* pNode = pIt->First();

	while (!pIt->IsDone())
	{
		Voice* pDelete = (Voice*)pIt->Curr();
		pNode = pIt->Next();
		delete pDelete;
	}

	pIt = this->baseGetReserveIterator();

	pNode = pIt->First();

	while (!pIt->IsDone())
	{
		Voice* pDelete = (Voice*)pIt->Curr();
		pNode = pIt->Next();
		delete pDelete;
	}
}

void VoiceMan::Create(int reserveNum, int reserveGrow)
{
	if (pInstance == nullptr)
	{
		pInstance = new VoiceMan(reserveNum, reserveGrow);
	}
}

void VoiceMan::Destroy()
{
	delete VoiceMan::pInstance;
	VoiceMan::pInstance = nullptr;
}

Voice* VoiceMan::Add(Wave::ID wave_Id, VoiceCallBack* pCallBack)
{
	VoiceMan* pMan = VoiceMan::GetInstance();
	Wave* pWave = WaveMan::Find(wave_Id);
	Voice* pNode = (Voice*)pMan->baseAddToFront();
	pNode->Set(pWave, pCallBack);
	return pNode;
}

void VoiceMan::Remove(Voice* pNode)
{
	VoiceMan* pMan = VoiceMan::GetInstance();
	pMan->baseRemove(pNode);
}


void VoiceMan::Dump()
{
	VoiceMan* pMan = VoiceMan::GetInstance();
	assert(pMan != nullptr);

	pMan->baseDump();
}

VoiceMan* VoiceMan::GetInstance()
{
	return pInstance;
}

DLink* VoiceMan::derivedCreateNode()
{
	DLink* pNodeBase = new Voice();
	return pNodeBase;
}