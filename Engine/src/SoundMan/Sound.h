#ifndef SOUND_H
#define SOUND_H

#include "Handle.h"
#include "DLink.h"
#include "Sound.h"
#include "AnimTime.h"

class ASound;
class UserSoundCallBack;

class Sound : public DLink
{
public:
	enum class ID
	{
		Fiddle = 0x77770000,
		Bassoon,
		Strings,
		Calliope,
		Oboe,
		SongA,
		SongB,
		Seinfeld,
		Beethoven,
		Alert,
		Electro,
		Coma,
		Dial,
		MoonPatrol,
		Sequence,
		Donkey,
		Intro,
		A,
		AtoB,
		B, 
		BtoC,
		C,
		CtoA,
		End,

		Uninitialized
	};

	typedef int Priority;
public:
	//constants
	static const unsigned int PRIORITY_TABLE_SIZE = 6;
	static const unsigned int LAST_ENTRY = PRIORITY_TABLE_SIZE - 1;
	static const int PRIORITY_TABLE_INVALID = -1;

public:
	class PriorityEntry
	{
	public:
		static const int PRIORITY_CLEAR = -1;
	public:
		PriorityEntry();
		PriorityEntry(const PriorityEntry&) = default;
		PriorityEntry& operator=(const PriorityEntry&) = default;
		~PriorityEntry() = default;

		void Clear();

		//Data:
		Handle::ID handleID;
		Sound::ID soundID;
		int priority;
		Azul::AnimTime startTime;
		Sound* pSound;
		float pan;
	};

public:
	// Big 4
	Sound();
	Sound(const Sound&) = delete;
	Sound& operator = (const Sound&) = delete;
	virtual ~Sound();

	void Set(Sound::ID snd_id, UserSoundCallBack* pUserSndCallback, Sound::Priority priority);
	void Dump();
	void Wash();
	virtual bool Compare(DLink* pTargetNode) override;

	void Set(ASound* pASnd);
	ASound* GetASound();

	Azul::AnimTime GetTime();

	Handle::Status Play();
	Handle::Status Stop();
	Handle::Status SetVolume(float v);
	Handle::Status GetVolume(float &vol);
	Handle::Status Pan(float p);
	Handle::Status GetPan(float& pan);
	Handle::Status PanLeftOverTime(float start);
	Handle::Status PanRightOverTime(float start);
	Handle::Status SetVolumeUpOT(float start);
	Handle::Status SetVolumeDownOT(float start);

	void RemoveFromPriorityTable();

	static void KillAllActive();
	static void SortPriorityTable();
	static void PrintPriorityTable();

private:
	void Clear();
	bool UseOpenSlotInTable();


public:
	//----------------------------------------------------
	// Data
	//----------------------------------------------------
	Sound::ID sound_id;
	Sound::Priority priority;
	ASound* pASound;

	float mVol;
	float mPan;

	Handle handle;

	//Table
	static PriorityEntry PriorityTable[PRIORITY_TABLE_SIZE];
	static std::mutex Table_mtx;
};


#endif // !SOUND_H
