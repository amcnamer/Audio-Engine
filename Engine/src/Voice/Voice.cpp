
#include "XAudio2Wrapper.h"
#include "AudioEngine.h"
#include "Voice.h"
#include "StringEnum.h"

Voice::Voice()
	:pWave(nullptr),
	pBuff(nullptr),
	pCallback(nullptr),
	pSourceVoice(nullptr)
{
	Handle::IsValid(this->handle);
	this->pBuff = new XAUDIO2_BUFFER_ALIAS();

}
void Voice::Set(Wave* _pWave, VoiceCallBack* pCallBack)
{
	//Debug::out("voice::set(): %p\n", this);
	Handle::Status s;

	s = Handle::IsValid(this->handle);
	//assert(s == Handle::Status::INVALID_HANDLE);

	s = Handle::ActivateHandle(this->handle);
	assert(s == Handle::Status::VALID_HANDLE);

	assert(_pWave);
	this->pWave = _pWave;

	// transfer ownership
	assert(pCallBack);
	this->pCallback = pCallBack;

	IXAudio2* pXAudio2 = AudioEngine::GetXAudio2();
	assert(pXAudio2);

	// Create Source Voice
	this->pSourceVoice = nullptr;

	HRESULT hr;
	hr = pXAudio2->CreateSourceVoice(&this->pSourceVoice, (WAVEFORMATEX*)this->pWave->poWfx, 0, XAUDIO2_MAX_FREQ_RATIO, this->pCallback);
	assert(hr == S_OK);
	assert(this->pSourceVoice);

	// SourceBuffer
	assert(this->pBuff);
	this->InitSrcBuff();
	hr = this->pSourceVoice->SubmitSourceBuffer((XAUDIO2_BUFFER*)this->pBuff);
	assert(hr == S_OK);
	assert(this->pBuff);
}

Voice::~Voice()
{
	// Protection for empty voices
	if (this->pSourceVoice)
	{
		this->pSourceVoice->Stop();
		this->pSourceVoice->DestroyVoice();
		this->pSourceVoice = nullptr;
	}

	if (this->pBuff)
	{
		// Done in the wave manager
			//delete this->poBuff->pAudioData;
		delete this->pBuff;
		this->pBuff = nullptr;
	}

	if (this->pCallback)
	{
		delete this->pCallback;
		this->pCallback = nullptr;
	}
}

void Voice::InitSrcBuff()
{
	*pBuff = { 0 };
	pBuff->AudioBytes = pWave->rawBuffSize; //buffer containing audio data
	pBuff->pAudioData = pWave->poRawBuff;   //size of the audio buffer in bytes

	//pBuff->Flags = 0;   // tell the source voice to expect more data after this buffer
	pBuff->Flags = XAUDIO2_END_OF_STREAM;   // tell the source voice not to expect any data after this buffer

	pBuff->LoopCount = 0;				     // looping...
}

void Voice::Wash()
{
	this->Clear();
}

void Voice::Dump()
{
	if (this->pWave)
	{
		Trace::out("\t\tVoice(%p): %s \n", this, StringMe(this->pWave->GetId()));
	}
	else
	{
		Trace::out("\t\tVoice(%p): --- \n", this);
	}
}

bool Voice::Compare(DLink*)
{
	return false;
}

void Voice::Clear()
{
	*this->pBuff = { 0 };

	if (this->pCallback)
	{
		delete this->pCallback;
		this->pCallback = nullptr;
	}

	if (this->pSourceVoice)
	{
		this->pSourceVoice->Stop();
		this->pSourceVoice->DestroyVoice();
		this->pSourceVoice = nullptr;
	}

	//Debug::out(" voice::clear()  %p\n", this);
	// validate when used in Set

	Handle::Status s = Handle::IsValid(this->handle);
	//assert(s == Handle::Status::VALID_HANDLE);

	s = Handle::InvalidateHandle(this->handle);
	assert(s == Handle::Status::INVALID_HANDLE);
}

Handle::Status Voice::Start()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		HRESULT hr;
		hr = pSourceVoice->Start(0);
	}
	return lock;
}

Handle::Status  Voice::Pause()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		HRESULT hr;
		hr = pSourceVoice->Stop();
		assert(hr == S_OK);
	}

	return lock;
}

Handle::Status  Voice::Stop()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		HRESULT hr;
		hr = pSourceVoice->Stop(0);
		assert(hr == S_OK);
		pSourceVoice->FlushSourceBuffers();
	}

	return lock;
}

Handle::Status Voice::PanVoice(float val)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// Get the Audio Engine... 
		IXAudio2MasteringVoice* pMasterVoice = AudioEngine::GetMasterVoice();

		assert(pMasterVoice);
		assert(this->pSourceVoice);

		DWORD dwChannelMask;
		pMasterVoice->GetChannelMask(&dwChannelMask);

		// SPEAKER_STEREO // SPEAKER_FRONT_LEFT (0x1) | SPEAKER_FRONT_RIGHT (0x2)
		assert(dwChannelMask == 0x3);

		// pan of -1.0 indicates all left speaker, 
		// 1.0 is all right speaker, 0.0 is split between left and right
		float left = 0.5f -  val / 2;
		float right = 0.5f + val / 2;

		float outputMatrix[8];
		for (int i = 0; i < 8; i++)
		{
			outputMatrix[i] = 0;
		}

		outputMatrix[0] = left;
		outputMatrix[1] = right;

		// Assuming pVoice sends to pMasteringVoice
		XAUDIO2_VOICE_DETAILS VoiceDetails;
		this->pSourceVoice->GetVoiceDetails(&VoiceDetails);

		XAUDIO2_VOICE_DETAILS MasterVoiceDetails;
		pMasterVoice->GetVoiceDetails(&MasterVoiceDetails);

		if (this->pSourceVoice->SetOutputMatrix(NULL, VoiceDetails.InputChannels, MasterVoiceDetails.InputChannels, outputMatrix) != S_OK)
		{
			assert(false);
		}
	}
	else
	{
		assert(false);
	}

	return lock;
}


Handle::Status Voice::SetVolume(float val)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		HRESULT hr;
		hr = pSourceVoice->SetVolume(val);
		assert(hr == S_OK);
	}
	return lock;
}
Handle::Status Voice::GetVolume(float* val)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		pSourceVoice->GetVolume(val);
	}
	return lock;
}

