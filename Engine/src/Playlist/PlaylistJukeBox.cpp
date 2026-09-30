
#include "PlaylistJukeBox.h"
#include "Audio_LoadPlaylist_Command.h"
#include "QueueMan.h"
#include "Internal_Playlist_CallBack.h"

PlaylistJukeBox* PlaylistJukeBox::pInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
PlaylistJukeBox::PlaylistJukeBox(int reserveNum, int reserveGrow)
	: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
	// Preload the reserve
	this->proFillReservedPool(reserveNum);

	// initialize derived data here
	this->poNodeCompare = new Playlist();
}

PlaylistJukeBox::~PlaylistJukeBox()
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
void PlaylistJukeBox::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new PlaylistJukeBox(reserveNum, reserveGrow);
	}

}

void PlaylistJukeBox::Destroy()
{
	PlaylistJukeBox* pMan = PlaylistJukeBox::GetInstance();
	assert(pMan != nullptr);

	delete PlaylistJukeBox::pInstance;
	PlaylistJukeBox::pInstance = nullptr;
}

void PlaylistJukeBox::Load(Sound::ID snd_id,PlaylistCommand* pPlaylistCmd,VoiceCallBack* pVoiceCallbackA,
	Wave::ID VoiceA,VoiceCallBack* pVoiceCallbackB,Wave::ID VoiceB)
{
	assert(pPlaylistCmd);
	assert(pVoiceCallbackA);

	bool finished = false;
	Internal_Playlist_CallBack* pCallBack = new Internal_Playlist_CallBack(finished);

	Audio_LoadPlaylist_Command* pCmd = new Audio_LoadPlaylist_Command(snd_id,pPlaylistCmd,pVoiceCallbackA,
		VoiceA,pVoiceCallbackB,VoiceB, pCallBack);
	assert(pCmd);

	QueueMan::SendAudio(pCmd);
	while (!finished);
}

Playlist* PlaylistJukeBox::Add(Sound::ID snd_id,PlaylistCommand* pPlaylistCmd,VoiceCallBack* pVoiceCallbackA,
	Wave::ID VoiceA,VoiceCallBack* pVoiceCallbackB,Wave::ID VoiceB)
{
	PlaylistJukeBox* pMan = PlaylistJukeBox::GetInstance();

	Playlist* pNode = (Playlist*)pMan->baseAddToFront();
	assert(pNode != nullptr);

	// Initialize the data
	pNode->Set(snd_id,pPlaylistCmd,pVoiceCallbackA,VoiceA,pVoiceCallbackB,VoiceB);

	return pNode;
}

Playlist* PlaylistJukeBox::Find(Sound::ID _id)
{
	PlaylistJukeBox* pMan = PlaylistJukeBox::GetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->id = _id;

	Playlist* pData = (Playlist*)pMan->baseFind(pMan->poNodeCompare);
	return pData;
}

void PlaylistJukeBox::Remove(Playlist* pNode)
{
	assert(pNode != nullptr);

	PlaylistJukeBox* pMan = PlaylistJukeBox::GetInstance();
	assert(pMan != nullptr);

	pMan->baseRemove(pNode);
}

void PlaylistJukeBox::Dump()
{
	PlaylistJukeBox* pMan = PlaylistJukeBox::GetInstance();
	assert(pMan != nullptr);

	pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
PlaylistJukeBox* PlaylistJukeBox::GetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* PlaylistJukeBox::derivedCreateNode()
{
	DLink* pNodeBase = new Playlist();
	assert(pNodeBase != nullptr);

	return pNodeBase;
}

