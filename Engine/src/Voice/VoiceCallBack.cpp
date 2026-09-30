
#include "VoiceCallBack.h"
#include "ASound.h"
#include "Voice.h"



VoiceCallBack::VoiceCallBack()
	: status(VoiceCallBack::Status::Uninitialzed),
	pASound(nullptr),
	pVoice(nullptr)
{
	// pASnd is set externally
	// pVoice is set externally
}

VoiceCallBack::VoiceCallBack(const VoiceCallBack&)
	: status(VoiceCallBack::Status::Uninitialzed),
	pASound(nullptr),
	pVoice(nullptr)
{
	// pASnd is set externally
	// pVoice is set externally
}

void VoiceCallBack::SetVoice(Voice* _pVoice)
{
	assert(_pVoice);
	this->pVoice = _pVoice;
}

void VoiceCallBack::SetASound(ASound* _pASnd)
{
	assert(_pASnd);
	this->pASound = _pASnd;
}
