
#ifndef VOICE_CALLBACK_H
#define VOICE_CALLBACK_H

#include "XAudio2Wrapper.h"

class Voice;
class ASound;

// Sample voice callback
class VoiceCallBack : public IXAudio2VoiceCallback
{
public:
	enum class Status
	{
		Ready,
		Started,
		Stopped,
		Finished,
		Uninitialzed
	};

public:

	VoiceCallBack();
	VoiceCallBack(const VoiceCallBack&);
	VoiceCallBack(VoiceCallBack&&) = delete;
	VoiceCallBack& operator = (const VoiceCallBack&) = delete;
	VoiceCallBack& operator = (VoiceCallBack&&) = delete;
	virtual ~VoiceCallBack() = default;

	virtual VoiceCallBack* CreateCallBackCopy() = 0;

	void SetVoice(Voice* pVoice);
	void SetASound(ASound* pASnd);

	// ----------------------
	//    Data
	// ----------------------
	Status status;
	ASound* pASound;
	Voice* pVoice;
};

#endif // !VOICE_CALLBACK_H
