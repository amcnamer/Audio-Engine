
#include "Sound.h"
#include "SoundManager.h"
#include "StringEnum.h"
#include "Audio_CreateSound_Command.h"
#include "Audio_PlaySound_Command.h"
#include "Audio_StopSound_Command.h"
#include "Audio_SetSoundVolume_Command.h"
#include "Audio_PanSound_Command.h"
#include "QueueMan.h"
#include "TimerMan.h"
#include "HandleMan.h"
#include "Audio_PanSoundLeftOT_Command.h"
#include "Audio_PanSoundRightOT_Command.h"
#include "Audio_VolumeUpOT_Command.h"
#include "Audio_VolumeDownOT_Command.h"

#include <algorithm>

//static store
Sound::PriorityEntry Sound::PriorityTable[PRIORITY_TABLE_SIZE];
std::mutex Sound::Table_mtx;

Sound::Sound()
	:sound_id(Sound::ID::Uninitialized),
	priority(0),
	pASound(nullptr),
	mVol(0.5f),
	mPan(0.0f),
	handle()
{

}

Sound::~Sound()
{

}

void Sound::Set(Sound::ID _sound_id, UserSoundCallBack *pUserSoundCallBack, Sound::Priority _priority)
{
	this->sound_id = _sound_id;
	this->priority = _priority;

	Handle::ActivateHandle(this->handle);

	// Send a command to create ASnd
	Audio_CreateSound_Command* pCmd = new Audio_CreateSound_Command(this->sound_id, this, pUserSoundCallBack);
	assert(pCmd);

	//Debug::out("--> Audio_CreateSound_Command \n");
	QueueMan::SendAudio(pCmd);
}

void Sound::Set(ASound* _pASnd)
{
	assert(_pASnd);
	this->pASound = _pASnd;
}

ASound* Sound::GetASound()
{
	assert(pASound);
	return this->pASound;
}

void Sound::Dump()
{
	// Dump - Print contents to the debug output window
	Trace::out("\t\tSound(%p) %s  ASound(%p)\n", this, StringMe(this->sound_id), this->pASound);
}

void Sound::Clear()
{
	this->sound_id = Sound::ID::Uninitialized;
	this->priority = 0;
	this->pASound = nullptr;
	HandleMan::InvalidateHandle(this->handle);
}

void Sound::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->Clear();
}

bool Sound::Compare(DLink* pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	Sound* pDataB = (Sound*)pTarget;

	bool status = false;

	if (this->sound_id == pDataB->sound_id)
	{
		status = true;
	}

	return status;
}

void Sound::KillAllActive()
{
	std::lock_guard<std::mutex> lock(Sound::Table_mtx);
	for (unsigned int i = 0; i < Sound::PRIORITY_TABLE_SIZE; i++)
	{
		Sound* pSound = Sound::PriorityTable[i].pSound;
		if (pSound != nullptr)
		{
			pSound->Stop();
			Sound::PriorityTable[i].Clear();
		}
	}
}

Handle::Status Sound::Play()
{
	Handle::Lock lock(this->handle);

	Debug::out("Play(%s) priority:%d hdl:0x%x\n", StringMe(this->sound_id), this->priority, this->handle.GetID());

	if (lock)
	{
		if (this->UseOpenSlotInTable())
		{
			// Easy take a slot
			Audio_PlaySound_Command* pCmd = new Audio_PlaySound_Command(this->sound_id, this);
			assert(pCmd);

			//	Debug::out("--> Audio_PlayASnd_Cmd \n");
			QueueMan::SendAudio(pCmd);
		}
		else
		{
			// No - Slots
			// Can I preempt the sound?
			// Table is sorted... so look at last slot only
			if (this->priority <= Sound::PriorityTable[LAST_ENTRY].priority)
			{
				// Priority kill the existing sound
				Sound* pSnd = Sound::PriorityTable[LAST_ENTRY].pSound;
				assert(pSnd);

				Debug::out("--> Priority Kill(%s): 0x%x \n", StringMe(pSnd->sound_id), pSnd->handle.GetID());

				pSnd->Stop();
				pSnd->RemoveFromPriorityTable();
				Sound::PrintPriorityTable();

				this->UseOpenSlotInTable();

				// Easy take a slot
				Audio_PlaySound_Command* pCmd = new Audio_PlaySound_Command(this->sound_id, this);
				assert(pCmd);

				//Debug::out("--> Audio_PlayASnd_Cmd \n");
				QueueMan::SendAudio(pCmd);
			}
			else
			{
				Debug::out("Reject --> Play(%s) priority:%d hdl:0x%x\n", StringMe(this->sound_id), this->priority, this->handle.GetID());

			}
		}
	}
	return lock;
}


Handle::Status Sound::Stop()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		Audio_StopSound_Command* pCmd = new Audio_StopSound_Command(this->sound_id, this);
		assert(pCmd);

		//Debug::out("--> Audio_StopSnd_Cmd stop\n");
		QueueMan::SendAudio(pCmd);
	}

	return lock;
}

Handle::Status Sound::SetVolume(float vol)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->mVol = vol;
		Audio_SetSoundVolume_Command* pCmd = new Audio_SetSoundVolume_Command(this->sound_id, this, vol);
		assert(pCmd);

		//Debug::out("--> Audio_SetSoundVolume_Command  vol:%f \n", vol);
		QueueMan::SendAudio(pCmd);
	}

	return lock;
}

Handle::Status Sound::GetVolume(float &vol)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		vol = this->mVol;
	}

	return lock;
}

Handle::Status Sound::SetVolumeUpOT(float vol)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->mVol = vol;
		Audio_VolumeUpOT_Command* pCmd = new Audio_VolumeUpOT_Command(this->sound_id, this, vol);
		assert(pCmd);

		//Debug::out("--> Audio_SetSoundVolume_Command  vol:%f \n", vol);
		QueueMan::SendAudio(pCmd);
	}

	return lock;
}

Handle::Status Sound::SetVolumeDownOT(float vol)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->mVol = vol;
		Audio_VolumeDownOT_Command* pCmd = new Audio_VolumeDownOT_Command(this->sound_id, this, vol);
		assert(pCmd);

		//Debug::out("--> Audio_SetSoundVolume_Command  vol:%f \n", vol);
		QueueMan::SendAudio(pCmd);
	}

	return lock;
}

Handle::Status Sound::Pan(float pan)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->mPan = pan;
		Audio_PanSound_Command* pCmd = new Audio_PanSound_Command(this->sound_id, this, pan);
		assert(pCmd);

		//Debug::out("--> Audio_PanSound_Command pan:%f \n", pan);
		QueueMan::SendAudio(pCmd);
	}

	return lock;
}

Handle::Status Sound::GetPan(float& pan)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// local copy
		pan = this->mPan;
	}

	return lock;
}

Handle::Status Sound::PanLeftOverTime(float start)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->mPan = start;
		Audio_PanSoundLeftOT_Command* pCmd = new Audio_PanSoundLeftOT_Command(this->sound_id, this, start);
		assert(pCmd);

		//Debug::out("--> Audio_PanSound_Command pan:%f \n", pan);
		QueueMan::SendAudio(pCmd);
	}

	return lock;
}

Handle::Status Sound::PanRightOverTime(float start)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->mPan = start;
		Audio_PanSoundRightOT_Command* pCmd = new Audio_PanSoundRightOT_Command(this->sound_id, this, start);
		assert(pCmd);

		//Debug::out("--> Audio_PanSound_Command pan:%f \n", pan);
		QueueMan::SendAudio(pCmd);
	}

	return lock;
}

Sound::PriorityEntry::PriorityEntry()
{
	this->Clear();
}

void Sound::PriorityEntry::Clear()
{
	this->priority = PriorityEntry::PRIORITY_CLEAR;
	this->soundID = Sound::ID::Uninitialized;
	this->handleID = 0;
	this->startTime = Azul::AnimTime(Azul::AnimTime::Duration::ZERO);
	this->pSound = nullptr;
}

void Sound::RemoveFromPriorityTable()
{
	std::lock_guard<std::mutex> lock(Sound::Table_mtx);

	bool status = false;

	for (unsigned int i = 0; i < Sound::PRIORITY_TABLE_SIZE; i++)
	{
		if (Sound::PriorityTable[i].handleID == this->handle.GetID())
		{
			Sound::PriorityTable[i].Clear();
			status = true;
			break;
		}
	}

	Sound::SortPriorityTable();
}

bool sortFunc(Sound::PriorityEntry a, Sound::PriorityEntry b)
{
	if (a.priority < b.priority)
	{
		return true;
	}
	else if (a.priority == b.priority)
	{
		if (a.startTime > b.startTime)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void Sound::SortPriorityTable()
{
	std::sort(std::begin(Sound::PriorityTable),
		std::end(Sound::PriorityTable),
		sortFunc);
}

bool Sound::UseOpenSlotInTable()
{
	std::lock_guard<std::mutex> lock(Sound::Table_mtx);

	bool status = false;

	// Find open slot?
	for (unsigned int i = 0; i < Sound::PRIORITY_TABLE_SIZE; i++)
	{
		if (PriorityTable[i].priority == PriorityEntry::PRIORITY_CLEAR)
		{
			TimerMan::Update();
			PriorityTable[i].priority = this->priority;
			PriorityTable[i].soundID = this->sound_id;
			PriorityTable[i].handleID = this->handle.GetID();
			PriorityTable[i].startTime = TimerMan::GetTimeCurrent();
			PriorityTable[i].pSound = this;
			PriorityTable[i].pan = this->mPan;

			// Found one
			status = true;
			break;
		}
	}
	Sound::SortPriorityTable();
	return status;
}

Azul::AnimTime Sound::GetTime()
{
	std::lock_guard<std::mutex> lock(Sound::Table_mtx);

	Azul::AnimTime startTime;
	bool status = false;
	for (unsigned int i = 0; i < Sound::PRIORITY_TABLE_SIZE; i++)
	{
		if (Sound::PriorityTable[i].handleID == this->handle.GetID())
		{
			startTime = PriorityTable[i].startTime;
			status = true;
			break;
		}
	}

	assert(status);

	return startTime;
}

void Sound::PrintPriorityTable()
{
	std::lock_guard<std::mutex> lock(Sound::Table_mtx);

	size_t count = 720;
	char buff[720];
	char* pBuff = buff;
	int offset;

	offset = sprintf_s(pBuff, count, "---------------------------------\n");
	pBuff += offset;
	count -= offset;
	offset = sprintf_s(pBuff, count, " Snd Priority Table \n");
	pBuff += offset;
	count -= offset;
	offset = sprintf_s(pBuff, count, "---------------------------------\n");
	pBuff += offset;
	count -= offset;

	for (unsigned int i = 0; i < Sound::PRIORITY_TABLE_SIZE; i++)
	{
		if (Sound::PriorityTable[i].priority != PriorityEntry::PRIORITY_CLEAR)
		{
			Azul::AnimTime delta = (TimerMan::GetTimeCurrent()) - PriorityTable[i].startTime;

			offset = sprintf_s(pBuff,
				count,
				"hdl: 0x%x %-15s prior:%4d  time: %d ms  pan: %f\n",
				PriorityTable[i].handleID,
				StringMe(PriorityTable[i].soundID),
				PriorityTable[i].priority,
				Azul::AnimTime::Quotient(delta, Azul::AnimTime(Azul::AnimTime::Duration::ONE_MILLISECOND)),
				PriorityTable[i].pan);
		}
		else
		{
			offset = sprintf_s(pBuff,
				count,
				"hdl: 0x-------- Snd::---------- prior: ---  time: --- \n");
		}

		pBuff += offset;
		count -= offset;
	}

	sprintf_s(pBuff, count, "---------------------------------\n");
	pBuff += offset;
	count -= offset;

	Trace::out(buff);
}