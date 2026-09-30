
#ifndef VOICE_MAN_H
#define VOICE_MAN_H

#include "ManBase.h"
#include "DLinkMan.h"
#include "Voice.h"
#include "Wave.h"

class VoiceMan : public ManBase
{
private:
	VoiceMan(int reserveNum = 3, int reserveGrow = 1);
	~VoiceMan();

public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();
	static Voice* Add(Wave::ID wave_Id, VoiceCallBack* pCallBack);
	static void Remove(Voice* pNode);
	static void Dump();

private:
	static VoiceMan* GetInstance();

protected:
	DLink* derivedCreateNode() override;

private:
	Voice* pNodeCompare;
	static VoiceMan* pInstance;
};


#endif // !VOICE_MAN_H
