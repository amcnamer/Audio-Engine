
#include "SoundManager.h"
#include "QueueMan.h"

SoundManager* SoundManager::pInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
SoundManager::SoundManager(int reserveNum, int reserveGrow)
	: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
	// Preload the reserve
	this->proFillReservedPool(reserveNum);

	// initialize derived data here
	this->poNodeCompare = new Sound();
}

SoundManager::~SoundManager()
{
	// Debug::out("~Snd()\n");
	delete this->poNodeCompare;
	this->poNodeCompare = nullptr;

	// iterate through the list and delete
	Iterator* pIt = this->baseGetActiveIterator();

	DLink* pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		Sound* pDeleteMe = (Sound*)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}

	pIt = this->baseGetReserveIterator();

	pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		Sound* pDeleteMe = (Sound*)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void SoundManager::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new SoundManager(reserveNum, reserveGrow);
	}

}

void SoundManager::Destroy()
{
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan != nullptr);

	delete SoundManager::pInstance;
	SoundManager::pInstance = nullptr;
}

Sound* SoundManager::Add(Sound::ID snd_id, UserSoundCallBack* pUserSndCallback)
{
	return SoundManager::Add(snd_id, pUserSndCallback, SoundManager::DEFAULT_PRIORITY);
}

Sound* SoundManager::Add(Sound::ID snd_id, Sound::Priority priority)
{
	return SoundManager::Add(snd_id, nullptr, priority);
}

Sound* SoundManager::Add(Sound::ID snd_id)
{
	return SoundManager::Add(snd_id, nullptr, SoundManager::DEFAULT_PRIORITY);
}


Sound* SoundManager::Add(Sound::ID snd_id, UserSoundCallBack* pUserSoundCallBack, Sound::Priority priority)
{
	SoundManager* pMan = SoundManager::GetInstance();

	Sound* pNode = (Sound*)pMan->baseAddToFront();
	assert(pNode != nullptr);

	// Initialize the date
	pNode->Set(snd_id, pUserSoundCallBack, priority);

	return pNode;
}

void SoundManager::Update()
{
	Command* pCmd;
	CircularData* pGameIn = QueueMan::GetGameInQueue();

	if (pGameIn->PopFront(pCmd) == true)
	{
		assert(pCmd);
		pCmd->Execute();
	}
}

Sound* SoundManager::Find(Sound::ID _id)
{
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->sound_id = _id;

	Sound* pData = (Sound*)pMan->baseFind(pMan->poNodeCompare);
	return pData;
}

void SoundManager::Remove(Sound* pNode)
{
	assert(pNode != nullptr);

	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan != nullptr);

	pMan->baseRemove(pNode);
}

void SoundManager::Dump()
{
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan != nullptr);

	pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
SoundManager* SoundManager::GetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* SoundManager::derivedCreateNode()
{
	DLink* pNodeBase = new Sound();
	assert(pNodeBase != nullptr);

	return pNodeBase;
}