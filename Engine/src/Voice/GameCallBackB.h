
#ifndef GAME_CALLBACK_B_H
#define GAME_CALLBACK_B_H

#include "XAudio2Wrapper.h"
#include "VoiceCallBack.h"

//  Sample voice callback
class GameCallBackB : public VoiceCallBack
{
public:
	bool finished;

	GameCallBackB();
	GameCallBackB(const GameCallBackB&);
	GameCallBackB(GameCallBackB&&) = delete;
	GameCallBackB& operator = (const GameCallBackB&) = delete;
	GameCallBackB& operator = (GameCallBackB&&) = delete;
	virtual ~GameCallBackB() = default;

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