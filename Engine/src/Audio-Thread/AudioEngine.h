
#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "XAudio2Wrapper.h"
#include "CircularData.h"
#include "Voice.h"
#include "VoiceCallback.h"

class AudioEngine
{
public:
	AudioEngine();
	AudioEngine(const AudioEngine&) = delete;
	AudioEngine& operator=(const AudioEngine&) = delete;
	~AudioEngine();

	static IXAudio2* GetXAudio2();
	static IXAudio2MasteringVoice* GetMasterVoice();

	static void StartSound(Voice* pVoice);
	static void StopSound(Voice* pVoice);
	static void PauseSound(Voice* pVoice);
	static void PanSound(Voice* pVoice, float val);
	static void SetVolume(Voice* pVoice, float val);

private:
	void StartCOMThreads();
	void EndCOMThreads();
	void CreateXAudio2();
	void CreateMasterVoice();

private:
	static AudioEngine* GetInstance();
	static AudioEngine* pInstance;
	IXAudio2* pxAudio2;
	IXAudio2MasteringVoice* pMasterVoice;

};
#endif // !AUDIO_ENGINE_H
