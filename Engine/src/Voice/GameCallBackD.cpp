

#include "GameCallBackD.h"
#include "Audio_SoundEnd_Command.h"
#include "QueueMan.h"
#include "ASound.h"
#include "TimerEventMan.h"
#include "Demo4_KillCommand.h"

GameCallBackD::GameCallBackD()
	: VoiceCallBack(),
	finished(false)
{
}

GameCallBackD::GameCallBackD(const GameCallBackD&)
	: VoiceCallBack(),
	finished(false)
{
}

VoiceCallBack* GameCallBackD::CreateCallBackCopy()
{
	return new GameCallBackD(*this);
}

void __stdcall GameCallBackD::OnStreamEnd()
{
	finished = true;
	Debug::out("VoiceCallback: StreamEnd(%p)\n", this->pASound);
	Debug::out("WaveName: Donkey\n");
	this->pASound->pSound->PrintPriorityTable();
	Command* pCommand = new Demo4_KillCommand();
	TimerEventMan::Add(pCommand, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND));
}

void __stdcall GameCallBackD::OnVoiceProcessingPassEnd()
{
}

void __stdcall GameCallBackD::OnVoiceProcessingPassStart(UINT32)
{
	Debug::ChangeCurrentName("--XAUDIO2--");
}

void __stdcall GameCallBackD::OnBufferEnd(void*)
{
}

void __stdcall GameCallBackD::OnBufferStart(void*)
{
}

void __stdcall GameCallBackD::OnLoopEnd(void*)
{
}

void __stdcall GameCallBackD::OnVoiceError(void*, HRESULT)
{
}
