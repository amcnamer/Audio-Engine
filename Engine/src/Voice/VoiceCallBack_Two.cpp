
#include "VoiceCallback_Two.h"

VoiceCallBack_Two::VoiceCallBack_Two()
	:VoiceCallBack(),
	finished(false)
{
}

VoiceCallBack_Two::VoiceCallBack_Two(const VoiceCallBack_Two&)
	:VoiceCallBack(),
	finished(false)
{
}

VoiceCallBack_Two::~VoiceCallBack_Two()
{
}

VoiceCallBack* VoiceCallBack_Two::CreateCallBackCopy()
{
	return new VoiceCallBack_Two(*this);
}

void __stdcall VoiceCallBack_Two::OnStreamEnd()
{
	finished = true;
}

void __stdcall VoiceCallBack_Two::OnVoiceProcessingPassEnd()
{
}

void __stdcall VoiceCallBack_Two::OnVoiceProcessingPassStart(UINT32)
{
}

void __stdcall VoiceCallBack_Two::OnBufferEnd(void*)
{
}

void __stdcall VoiceCallBack_Two::OnBufferStart(void*)
{
}

void __stdcall VoiceCallBack_Two::OnLoopEnd(void*)
{
}

void __stdcall VoiceCallBack_Two::OnVoiceError(void*, HRESULT)
{
}
