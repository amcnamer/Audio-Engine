
#include "TimerEventMan.h"
#include "Audio.h"
#include "PlaylistJukeBox.h"
#include "VoiceCallBack_One.h"
#include "Playlist_OneVoice_Command.h"

#include "Demo1.h"
#include "Demo1_A_Command.h"


Demo1::Demo1(Azul::AnimTime time)
	:Demo(time)
{
	Trace::out("\n");
	Trace::out("******************************\n");
	Trace::out("**     DEMO 1 - Basics      **\n");
	Trace::out("******************************\n");
}
Demo1::~Demo1()
{

}

void Demo1::Load()
{

}

void Demo1::Execute()
{
	Trace::out("\n");
	Trace::out("--- DEMO 1: Execute() ----\n");

	Command* pCmd;
	pCmd = new Demo1_A_Command();
	TimerEventMan::Add(pCmd, 0 * Azul::AnimTime(Azul::AnimTime::Duration::ONE_SECOND));

}
