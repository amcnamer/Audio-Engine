
#ifndef VOICE_CALLBACK_STICHED_H
#define VOICE_CALLBACK_STICHED_H

#include "XAudio2Wrapper.h"
#include "VoiceCallBack.h"

#include "Wave.h"

class Voice;

//  Sample voice callback
class VoiceCallBack_Stitched : public VoiceCallBack
{
public:
	int count;
	bool   finished;
	Wave::ID* pWaveBuffList;
	int      waveBuffCount;

	VoiceCallBack_Stitched() = delete;
	VoiceCallBack_Stitched(const VoiceCallBack_Stitched&);
	VoiceCallBack_Stitched(VoiceCallBack_Stitched&&) = delete;
	VoiceCallBack_Stitched& operator = (const VoiceCallBack_Stitched&) = delete;
	VoiceCallBack_Stitched& operator = (VoiceCallBack_Stitched&&) = delete;
	virtual ~VoiceCallBack_Stitched();

	VoiceCallBack_Stitched(Wave::ID* pWaveBuffIDList, int _waveBuffCount);
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