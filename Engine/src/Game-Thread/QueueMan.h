#ifndef QUEUE_MAN_H
#define QUEUE_MAN_H

#include "CircularData.h"

class QueueMan
{
public:
	static void Create();
	static void Destroy();

	static bool SendAudio(Command* pCmd);
	static bool SendFile(Command* pCmd);
	static bool SendGame(Command* pCmd);
	static bool SendAux(Command* pCmd);

	static CircularData* GetGameInQueue();
	static CircularData* GetAudioInQueue();
	static CircularData* GetFileInQueue();
	static CircularData* GetAuxInQueue();

private:
	QueueMan();
	QueueMan(const QueueMan&) = delete;
	QueueMan& operator = (const QueueMan&) = delete;
	~QueueMan();

	static QueueMan* GetInstance();
	static QueueMan* psInstance;

	CircularData* pAudioIn; // ---> to Audio
	CircularData* pGameIn;  // ---> to Game
	CircularData* pFileIn;  // ---> to File
	CircularData* pAuxIn;   // ---> to Aux

};

#endif