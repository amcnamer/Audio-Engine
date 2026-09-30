

#include "VoiceCallBack_One.h"
#include "Audio_SoundEnd_Command.h"
#include "QueueMan.h"
#include "ASound.h"

VoiceCallBack_One::VoiceCallBack_One()
	: VoiceCallBack(),
	finished(false)
{
}

VoiceCallBack_One::VoiceCallBack_One(const VoiceCallBack_One&)
	: VoiceCallBack(),
	finished(false)
{
}

VoiceCallBack* VoiceCallBack_One::CreateCallBackCopy()
{
	return new VoiceCallBack_One(*this);
}

void __stdcall VoiceCallBack_One::OnStreamEnd()
{
	finished = true;
	Debug::out("VoiceCallback: StreamEnd(%p)\n", this->pASound);
	Audio_SoundEnd_Command* pCommand = new Audio_SoundEnd_Command(this->pASound->sound_id, this->pASound->pSound);
	Debug::out("--> Audio_SoundEnd_Command\n");
	QueueMan::SendAudio(pCommand);
}

void __stdcall VoiceCallBack_One::OnVoiceProcessingPassEnd()
{
}

void __stdcall VoiceCallBack_One::OnVoiceProcessingPassStart(UINT32)
{
		Debug::ChangeCurrentName("--XAUDIO2--");
}

void __stdcall VoiceCallBack_One::OnBufferEnd(void*)
{
}

void __stdcall VoiceCallBack_One::OnBufferStart(void*)
{
}

void __stdcall VoiceCallBack_One::OnLoopEnd(void*)
{
}

void __stdcall VoiceCallBack_One::OnVoiceError(void*, HRESULT)
{
}
