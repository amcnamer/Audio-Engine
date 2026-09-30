
#ifndef GAME_CALLBACK_C_H
#define GAME_CALLBACK_C_H

#include "XAudio2Wrapper.h"
#include "VoiceCallBack.h"

//  Sample voice callback
class GameCallBackC : public VoiceCallBack
{
public:
	bool finished;

	GameCallBackC();
	GameCallBackC(const GameCallBackC&);
	GameCallBackC(GameCallBackC&&) = delete;
	GameCallBackC& operator = (const GameCallBackC&) = delete;
	GameCallBackC& operator = (GameCallBackC&&) = delete;
	virtual ~GameCallBackC() = default;

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