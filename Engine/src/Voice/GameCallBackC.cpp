

#include "GameCallBackC.h"
#include "Audio_SoundEnd_Command.h"
#include "QueueMan.h"
#include "ASound.h"

GameCallBackC::GameCallBackC()
	: VoiceCallBack(),
	finished(false)
{
}

GameCallBackC::GameCallBackC(const GameCallBackC&)
	: VoiceCallBack(),
	finished(false)
{
}

VoiceCallBack* GameCallBackC::CreateCallBackCopy()
{
	return new GameCallBackC(*this);
}

void __stdcall GameCallBackC::OnStreamEnd()
{
	finished = true;
	Debug::out("VoiceCallback: StreamEnd(%p)\n", this->pASound);
	Debug::out("WaveName: Sequence\n");
	this->pASound->pSound->PrintPriorityTable();
}

void __stdcall GameCallBackC::OnVoiceProcessingPassEnd()
{
}

void __stdcall GameCallBackC::OnVoiceProcessingPassStart(UINT32)
{
	Debug::ChangeCurrentName("--XAUDIO2--");
}

void __stdcall GameCallBackC::OnBufferEnd(void*)
{
}

void __stdcall GameCallBackC::OnBufferStart(void*)
{
}

void __stdcall GameCallBackC::OnLoopEnd(void*)
{
}

void __stdcall GameCallBackC::OnVoiceError(void*, HRESULT)
{
}
