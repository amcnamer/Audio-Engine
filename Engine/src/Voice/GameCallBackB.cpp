

#include "GameCallBackB.h"
#include "Audio_SoundEnd_Command.h"
#include "QueueMan.h"
#include "ASound.h"

GameCallBackB::GameCallBackB()
	: VoiceCallBack(),
	finished(false)
{
}

GameCallBackB::GameCallBackB(const GameCallBackB&)
	: VoiceCallBack(),
	finished(false)
{
}

VoiceCallBack* GameCallBackB::CreateCallBackCopy()
{
	return new GameCallBackB(*this);
}

void __stdcall GameCallBackB::OnStreamEnd()
{
	finished = true;
	Debug::out("VoiceCallback: StreamEnd(%p)\n", this->pASound);
	Debug::out("WaveName: MoonPatrol\n");
	this->pASound->pSound->PrintPriorityTable();
}

void __stdcall GameCallBackB::OnVoiceProcessingPassEnd()
{
}

void __stdcall GameCallBackB::OnVoiceProcessingPassStart(UINT32)
{
	Debug::ChangeCurrentName("--XAUDIO2--");
}

void __stdcall GameCallBackB::OnBufferEnd(void*)
{
}

void __stdcall GameCallBackB::OnBufferStart(void*)
{
}

void __stdcall GameCallBackB::OnLoopEnd(void*)
{
}

void __stdcall GameCallBackB::OnVoiceError(void*, HRESULT)
{
}
