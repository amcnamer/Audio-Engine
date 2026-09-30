
#include "VoiceCallback_Stitched.h"
#include "WaveMan.h"
#include "XAudio2Wrapper.h"
#include "Voice.h"

VoiceCallBack_Stitched::VoiceCallBack_Stitched(const VoiceCallBack_Stitched&r)
	: VoiceCallBack(),
	count(0),
	finished(false),
	pWaveBuffList(nullptr),
	waveBuffCount(r.waveBuffCount)
{
	pWaveBuffList = new Wave::ID[waveBuffCount]();
	for (int i = 0; i < waveBuffCount; i++)
	{
		pWaveBuffList[i] = r.pWaveBuffList[i];
	}
	count++;
}

VoiceCallBack_Stitched::~VoiceCallBack_Stitched()
{
	delete this->pWaveBuffList;
	this->pWaveBuffList = nullptr;
}

VoiceCallBack_Stitched::VoiceCallBack_Stitched(Wave::ID* pWaveBuffIDList, int _waveBuffCount)
	: VoiceCallBack(),
	count(0),
	finished(false),
	pWaveBuffList(pWaveBuffIDList),
	waveBuffCount(_waveBuffCount)
{
	count++;
}

VoiceCallBack* VoiceCallBack_Stitched::CreateCallBackCopy()
{
	return new VoiceCallBack_Stitched(*this);
}

void __stdcall VoiceCallBack_Stitched::OnStreamEnd()
{
	finished = true;
}

void __stdcall VoiceCallBack_Stitched::OnVoiceProcessingPassEnd()
{
}

void __stdcall VoiceCallBack_Stitched::OnVoiceProcessingPassStart(UINT32)
{
}

void __stdcall VoiceCallBack_Stitched::OnBufferEnd(void*)
{

	// count is the number completed
	// Are there more?
	if (count < waveBuffCount)
	{
		XAUDIO2_BUFFER_ALIAS* pBuffer = this->pVoice->pBuff;
		assert(pBuffer);

		Wave* pWave = WaveMan::Find(pWaveBuffList[count]);
		assert(pWave);

		pBuffer->AudioBytes = pWave->rawBuffSize;
		pBuffer->pAudioData = pWave->poRawBuff;

		// Last one sent?
		if (count == (waveBuffCount - 1))
		{
			// Yes - end this voice, after this last buffer
			pBuffer->Flags = XAUDIO2_END_OF_STREAM;
		}

		HRESULT hr;

		if (FAILED(hr = this->pVoice->pSourceVoice->SubmitSourceBuffer((XAUDIO2_BUFFER*)pBuffer)))
		{
			assert(false);
		}
		
		Debug::out("Submitting %s to Buffer\n", pWave->strName);

		// num completed
		count++;
	}
}

void __stdcall VoiceCallBack_Stitched::OnBufferStart(void*)
{
}

void __stdcall VoiceCallBack_Stitched::OnLoopEnd(void*)
{
}

void __stdcall VoiceCallBack_Stitched::OnVoiceError(void*, HRESULT)
{
}
