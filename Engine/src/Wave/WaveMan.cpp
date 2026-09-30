
#include "WaveMan.h"
#include "Audio_LoadWave_Command.h"
#include "SoundManager.h"
#include "WaveTable.h"
#include "Audio.h"
#include "File_LoadFile_Command.h"
#include "File_AsyncLoadFile_Command.h"
#include "QueueMan.h"
#include "Aux_Internal_RemoveAllWavesCB_Command.h"

WaveMan* WaveMan::psInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
WaveMan::WaveMan(int reserveNum, int reserveGrow)
	: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
	// Preload the reserve
	this->proFillReservedPool(reserveNum);

	// initialize derived data here
	this->poNodeCompare = new Wave();
}

WaveMan::~WaveMan()
{
	//Debug::out("~WaveMan()\n");
	delete this->poNodeCompare;
	this->poNodeCompare = nullptr;

	// iterate through the list and delete
	Iterator* pIt = this->baseGetActiveIterator();

	DLink* pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		Wave* pDeleteMe = (Wave*)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}

	pIt = this->baseGetReserveIterator();

	pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		Wave* pDeleteMe = (Wave*)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void WaveMan::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(psInstance == nullptr);

	// Do the initialization
	if (psInstance == nullptr)
	{
		psInstance = new WaveMan(reserveNum, reserveGrow);
	}

}

void WaveMan::Destroy()
{
	WaveMan* pMan = WaveMan::GetInstance();
	assert(pMan != nullptr);

	delete WaveMan::psInstance;
	WaveMan::psInstance = nullptr;
}

void WaveMan::RemoveAll(Internal_FileCB_Command* pIFileCB)
{
	WaveMan* pMan = WaveMan::GetInstance();
	Iterator* pIt = pMan->baseGetActiveIterator();
	DLink* pNode = pIt->First();
	WaveTable* pWaveTable = Audio::GetWaveTable();
	while (!pIt->IsDone())
	{
		Wave* pDelete = (Wave*)pIt->Curr();
		pNode = pIt->Next();
		Wave::ID id = pDelete->id;
		pMan->Remove(pDelete);
		pWaveTable->Remove(id);
	}
	Aux_Internal_RemoveAllWavesCB_Command* pCommand = new Aux_Internal_RemoveAllWavesCB_Command(pIFileCB);

	QueueMan::SendAux(pCommand);
}

Wave* WaveMan::Add(Wave::ID wave_ID, const char* const pWaveName, UserAsyncLoadCallBack* pUserAsyncCB)
{
	WaveMan* pMan = WaveMan::GetInstance();
	Wave* pNode = (Wave*)pMan->baseAddToFront();
	pNode->SetPending(pWaveName, wave_ID, pUserAsyncCB);
	File_AsyncLoadFile_Command* pCommand = new File_AsyncLoadFile_Command(wave_ID, pWaveName, pNode);
	QueueMan::SendFile(pCommand);
	return pNode;
}

Wave* WaveMan::Add(Wave::ID wave_id, const char* const pWaveName, Internal_FileCB_Command *pFileCB)
{
	WaveMan* pMan = WaveMan::GetInstance();

	Wave* pNode = (Wave*)pMan->baseAddToFront();
	assert(pNode != nullptr);

	// Initialize the date
	pNode->SetPending(pWaveName, wave_id, pFileCB);

	File_LoadFile_Command* pCommand = new File_LoadFile_Command(wave_id, pWaveName, pNode);
	assert(pCommand);
	bool status = QueueMan::SendFile(pCommand);
	assert(status);

	return pNode;
}

Wave* WaveMan::Find(Wave::ID _id)
{
	WaveMan* pMan = WaveMan::GetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->id = _id;

	Wave* pData = (Wave*)pMan->baseFind(pMan->poNodeCompare);
	return pData;
}

void WaveMan::Remove(Wave* pNode)
{
	assert(pNode != nullptr);

	WaveMan* pMan = WaveMan::GetInstance();
	assert(pMan != nullptr);

	pMan->baseRemove(pNode);
}

void WaveMan::Dump()
{
	WaveMan* pMan = WaveMan::GetInstance();
	assert(pMan != nullptr);

	pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
WaveMan* WaveMan::GetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(psInstance != nullptr);

	return psInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* WaveMan::derivedCreateNode()
{
	DLink* pNodeBase = new Wave();
	assert(pNodeBase != nullptr);

	return pNodeBase;
}

// --- End of File ---
