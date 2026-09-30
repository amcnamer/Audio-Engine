
#ifndef GAME_CALLBACK_D_H
#define GAME_CALLBACK_D_H

#include "XAudio2Wrapper.h"
#include "VoiceCallBack.h"

//  Sample voice callback
class GameCallBackD : public VoiceCallBack
{
public:
	bool finished;

	GameCallBackD();
	GameCallBackD(const GameCallBackD&);
	GameCallBackD(GameCallBackD&&) = delete;
	GameCallBackD& operator = (const GameCallBackD&) = delete;
	GameCallBackD& operator = (GameCallBackD&&) = delete;
	virtual ~GameCallBackD() = default;

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