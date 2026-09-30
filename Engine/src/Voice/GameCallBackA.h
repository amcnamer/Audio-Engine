
#ifndef GAME_CALLBACK_A_H
#define GAME_CALLBACK_A_H

#include "XAudio2Wrapper.h"
#include "VoiceCallBack.h"

//  Sample voice callback
class GameCallBackA : public VoiceCallBack
{
public:
	bool finished;

	GameCallBackA();
	GameCallBackA(const GameCallBackA&);
	GameCallBackA(GameCallBackA&&) = delete;
	GameCallBackA& operator = (const GameCallBackA&) = delete;
	GameCallBackA& operator = (GameCallBackA&&) = delete;
	virtual ~GameCallBackA() = default;

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