
#include "AudioEngine.h"
#include "VoiceCallback.h"

AudioEngine* AudioEngine::pInstance = nullptr;

AudioEngine::AudioEngine()
	:pxAudio2(nullptr),
	pMasterVoice(nullptr)
{
	this->StartCOMThreads();
	this->CreateXAudio2();
	this->CreateMasterVoice();
	AudioEngine::pInstance = this;
}

IXAudio2MasteringVoice* AudioEngine::GetMasterVoice()
{
	AudioEngine* pAudio = AudioEngine::GetInstance();
	return pAudio->pMasterVoice;
}

IXAudio2* AudioEngine::GetXAudio2()
{
	AudioEngine* pAudio = AudioEngine::GetInstance();
	return pAudio->pxAudio2;
}

AudioEngine* AudioEngine::GetInstance()
{
	return AudioEngine::pInstance;
}

AudioEngine::~AudioEngine()
{
	this->pMasterVoice->DestroyVoice();
	this->pxAudio2->Release();
	this->EndCOMThreads();
}

void AudioEngine::StartCOMThreads()
{
	HRESULT hr;
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	assert(hr == S_OK);
}

void AudioEngine::EndCOMThreads()
{
	CoUninitialize();
}

void AudioEngine::CreateXAudio2()
{
	HRESULT hr;
	hr = XAudio2Create(&this->pxAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(hr == S_OK);
}

void AudioEngine::CreateMasterVoice()
{
	// -------------------------------------------------------
	// Creating a master voice, with default settings:
	//
	//      InputChannels = XAUDIO2_DEFAULT_CHANNELS,
	//      InputSampleRate = XAUDIO2_DEFAULT_SAMPLERATE,
	//      Flags = 0,
	//      szDeviceId = NULL,
	//      *pEffectChain = NULL,
	//      StreamCategory = AudioCategory_GameEffects
	// -------------------------------------------------------
	HRESULT hr;
	hr = this->pxAudio2->CreateMasteringVoice(&this->pMasterVoice);
	assert(hr == S_OK);
}

void AudioEngine::StartSound(Voice* pVoice)
{
	//Start source Voice
	Handle::Status status;
	status = pVoice->Start();
	assert(status == Handle::Status::SUCCESS);
}

void AudioEngine::StopSound(Voice* pVoice)
{
	//Stop source Voice
	Handle::Status status;
	status = pVoice->Stop();
	assert(status == Handle::Status::SUCCESS);
}

void AudioEngine::PauseSound(Voice* pVoice)
{
	//Pause source Voice
	Handle::Status status;
	status = pVoice->Pause();
	assert(status == Handle::Status::SUCCESS);
}

void AudioEngine::PanSound(Voice* pVoice, float val)
{
	//Pause source Voice
	Handle::Status status;
	status = pVoice->PanVoice(val);
	assert(status == Handle::Status::SUCCESS);
}

void AudioEngine::SetVolume(Voice* pVoice, float val)
{
	//Pause source Voice
	Handle::Status status;
	status = pVoice->SetVolume(val);
	assert(status == Handle::Status::SUCCESS);
}
