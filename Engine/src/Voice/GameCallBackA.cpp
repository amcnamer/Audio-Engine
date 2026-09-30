

#include "GameCallBackA.h"
#include "Audio_SoundEnd_Command.h"
#include "QueueMan.h"
#include "ASound.h"

GameCallBackA::GameCallBackA()
	: VoiceCallBack(),
	finished(false)
{
}

GameCallBackA::GameCallBackA(const GameCallBackA&)
	: VoiceCallBack(),
	finished(false)
{
}

VoiceCallBack* GameCallBackA::CreateCallBackCopy()
{
	return new GameCallBackA(*this);
}

void __stdcall GameCallBackA::OnStreamEnd()
{
	finished = true;
	Debug::out("VoiceCallback: StreamEnd(%p)\n", this->pASound);
	Debug::out("WaveName: Dial\n");
	this->pASound->pSound->PrintPriorityTable();
}

void __stdcall GameCallBackA::OnVoiceProcessingPassEnd()
{
}

void __stdcall GameCallBackA::OnVoiceProcessingPassStart(UINT32)
{
	Debug::ChangeCurrentName("--XAUDIO2--");
}

void __stdcall GameCallBackA::OnBufferEnd(void*)
{
}

void __stdcall GameCallBackA::OnBufferStart(void*)
{
}

void __stdcall GameCallBackA::OnLoopEnd(void*)
{
}

void __stdcall GameCallBackA::OnVoiceError(void*, HRESULT)
{
}
