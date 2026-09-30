


#ifndef VOICE_CALLBACK_TWO_H
#define VOICE_CALLBACK_TWO_H

#include "XAudio2Wrapper.h"
#include "VoiceCallback.h"

//  Sample voice callback
class VoiceCallBack_Two : public VoiceCallBack
{
public:
	bool   finished;

	VoiceCallBack_Two();
	VoiceCallBack_Two(const VoiceCallBack_Two&);
	VoiceCallBack_Two(VoiceCallBack_Two&&) = delete;
	VoiceCallBack_Two& operator = (const VoiceCallBack_Two&) = delete;
	VoiceCallBack_Two& operator = (VoiceCallBack_Two&&) = delete;
	virtual ~VoiceCallBack_Two();

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