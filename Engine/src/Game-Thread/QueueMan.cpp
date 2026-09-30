#include "QueueMan.h"

QueueMan* QueueMan::psInstance = nullptr;

QueueMan::QueueMan()
{
	pAudioIn = new CircularData();
	pGameIn = new CircularData();
	pFileIn = new CircularData();
	pAuxIn = new CircularData();
}

QueueMan::~QueueMan()
{
	delete this->pAudioIn;
	this->pAudioIn = nullptr;

	delete this->pGameIn;
	this->pGameIn = nullptr;

	delete this->pFileIn;
	this->pFileIn = nullptr;

	delete this->pAuxIn;
	this->pAuxIn = nullptr;
}

void QueueMan::Create()
{
	if (psInstance == nullptr)
	{
		psInstance = new QueueMan();
	}
}

void QueueMan::Destroy()
{
	delete QueueMan::psInstance;
	QueueMan::psInstance = nullptr;
}

bool QueueMan::SendAudio(Command* pCommand)
{
	QueueMan* pMan = QueueMan::GetInstance();
	bool status = pMan->pAudioIn->PushBack(pCommand);
	return status;
}

bool QueueMan::SendFile(Command* pCommand)
{
	QueueMan* pMan = QueueMan::GetInstance();
	bool status = pMan->pFileIn->PushBack(pCommand);
	return status;
}

bool QueueMan::SendGame(Command* pCommand)
{
	QueueMan* pMan = QueueMan::GetInstance();
	bool status = pMan->pGameIn->PushBack(pCommand);
	return status;
}

bool QueueMan::SendAux(Command* pCommand)
{
	QueueMan* pMan = QueueMan::GetInstance();
	bool status = pMan->pAuxIn->PushBack(pCommand);
	return status;
}

CircularData* QueueMan::GetGameInQueue()
{
	QueueMan* pMan = QueueMan::GetInstance();
	return pMan->pGameIn;
}

CircularData* QueueMan::GetAudioInQueue()
{
	QueueMan* pMan = QueueMan::GetInstance();
	return pMan->pAudioIn;
}

CircularData* QueueMan::GetFileInQueue()
{
	QueueMan* pMan = QueueMan::GetInstance();
	return pMan->pFileIn;
}

CircularData* QueueMan::GetAuxInQueue()
{
	QueueMan* pMan = QueueMan::GetInstance();
	return pMan->pAuxIn;
}

QueueMan* QueueMan::GetInstance()
{
	return psInstance;
}
