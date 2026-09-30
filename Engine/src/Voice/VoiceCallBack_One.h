
#ifndef VOICE_CALLBACK_ONE_H
#define VOICE_CALLBACK_ONE_H

#include "XAudio2Wrapper.h"
#include "VoiceCallBack.h"

//  Sample voice callback
class VoiceCallBack_One : public VoiceCallBack
{
public:
	bool finished;

	VoiceCallBack_One();
	VoiceCallBack_One(const VoiceCallBack_One&);
	VoiceCallBack_One(VoiceCallBack_One&&) = delete;
	VoiceCallBack_One& operator = (const VoiceCallBack_One&) = delete;
	VoiceCallBack_One& operator = (VoiceCallBack_One&&) = delete;
	virtual ~VoiceCallBack_One() = default;

	virtual VoiceCallBack* CreateCallBackCopy() override;

	virtual void STDMETHODCALLTYPE OnStreamEnd() override;
	virtual void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() override;
	virtual void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32) override;
	virtual void STDMETHODCALLTYPE OnBufferEnd(void*) override;
	virtual void STDMETHODCALLTYPE OnBufferStart(void*) override;
	virtual void STDMETHODCALLTYPE OnLoopEnd(void*) override;
	virtual void STDMETHODCALLTYPE OnVoiceError(void*, HRESULT) override;
};

#endif