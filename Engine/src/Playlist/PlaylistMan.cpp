
#include "PlaylistMan.h"
#include "Audio_LoadPlaylist_Command.h"
#include "QueueMan.h"

PlaylistMan* PlaylistMan::pInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
PlaylistMan::PlaylistMan(int reserveNum, int reserveGrow)
	: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
	// Preload the reserve
	this->proFillReservedPool(reserveNum);

	// initialize derived data here
	this->poNodeCompare = new Playlist();
}

PlaylistMan::~PlaylistMan()
{
	// Debug::out("~Playlist()\n");
	delete this->poNodeCompare;
	this->poNodeCompare = nullptr;

	// iterate through the list and delete
	Iterator* pIt = this->baseGetActiveIterator();

	DLink* pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		Playlist* pDeleteMe = (Playlist*)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}

	pIt = this->baseGetReserveIterator();

	pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		Playlist* pDeleteMe = (Playlist*)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void PlaylistMan::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new PlaylistMan(reserveNum, reserveGrow);
	}

}

void PlaylistMan::Destroy()
{
	PlaylistMan* pMan = PlaylistMan::GetInstance();
	assert(pMan != nullptr);

	delete PlaylistMan::pInstance;
	PlaylistMan::pInstance = nullptr;
}

Playlist* PlaylistMan::Add(ASound* pASnd,PlaylistCommand* pPlaylistCmd,VoiceCallBack* pVoiceCallbackA,Wave::ID VoiceA,
	VoiceCallBack* pVoiceCallbackB,Wave::ID VoiceB)
{
	PlaylistMan* pMan = PlaylistMan::GetInstance();

	Playlist* pNode = (Playlist*)pMan->baseAddToFront();
	assert(pNode != nullptr);

	// Initialize the date
	pNode->Set(pASnd,pPlaylistCmd,pVoiceCallbackA,VoiceA,pVoiceCallbackB,VoiceB);

	return pNode;
}

Playlist* PlaylistMan::Find(Sound::ID _id)
{
	PlaylistMan* pMan = PlaylistMan::GetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->id = _id;

	Playlist* pData = (Playlist*)pMan->baseFind(pMan->poNodeCompare);
	return pData;
}

void PlaylistMan::Remove(Playlist* pNode)
{
	assert(pNode != nullptr);

	PlaylistMan* pMan = PlaylistMan::GetInstance();
	assert(pMan != nullptr);

	pMan->baseRemove(pNode);
}

void PlaylistMan::Dump()
{
	PlaylistMan* pMan = PlaylistMan::GetInstance();
	assert(pMan != nullptr);

	pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
PlaylistMan* PlaylistMan::GetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* PlaylistMan::derivedCreateNode()
{
	DLink* pNodeBase = new Playlist();
	assert(pNodeBase != nullptr);

	return pNodeBase;
}

