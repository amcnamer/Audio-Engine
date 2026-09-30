
#include "VoiceCallback.h"
#include "AudioThread.h"
#include "XAudio2Wrapper.h"
#include "AudioEngine.h"
#include "Voice.h"
#include "VoiceMan.h"
#include "Wave.h"
#include "WaveMan.h"
#include "SoundManager.h"
#include "PlaylistMan.h"
#include "PlaylistJukeBox.h"
#include "ASoundMan.h"
#include "FileThread.h"
#include "QueueMan.h"
#include "AuxThread.h"

void Audio_Main(std::atomic_bool& QuitFlag, std::atomic_bool& AudioReadyFlag)
{
	SimpleBanner b;

	// Spawn Audio thread
	std::thread  t_File(File_Main, std::ref(QuitFlag));
	Debug::SetName(t_File, "--File--", 2);

	// Spawn Aux thread
	std::thread  t_Aux(Aux_Main, std::ref(QuitFlag));
	Debug::SetName(t_Aux, "--Aux --", 2);

	// Create the audio engine... 
	AudioEngine engine;

	WaveMan::Create();
	VoiceMan::Create();
	PlaylistJukeBox::Create();
	PlaylistMan::Create();
	ASoundMan::Create();

	CircularData* pAudioIn = QueueMan::GetAudioInQueue();

	AudioReadyFlag = true;

	// ----------------------------------------
	// Loop for ever until quit is hit
	// ----------------------------------------
	while (!QuitFlag)
	{
		Command* pCmd;

		if (pAudioIn->PopFront(pCmd) == true)
		{
			assert(pCmd);
			pCmd->Execute();
		}
	}

	ASoundMan::Destroy();
	PlaylistMan::Destroy();
	PlaylistJukeBox::Destroy();
	VoiceMan::Destroy();
	WaveMan::Destroy();

	t_Aux.join();
	t_File.join();

}