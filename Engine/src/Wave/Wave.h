
#ifndef WAVE_H
#define WAVE_H

#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "DLink.h"
#include "Internal_FileCB_Command.h"

class UserAsyncLoadCallBack;
typedef unsigned char RawData;

class Wave : public DLink
{
public:
	enum class Status
	{
		PENDING,
		READY,
		EMPTY
	};

	enum ID
	{
		Fiddle = 0x77770000,
		Bassoon,
		Strings,
		Calliope,
		Oboe,
		SongA,
		SongB,
		Empty,
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



		Not_Used
	};
	static const unsigned int NAME_SIZE = 256;

public:
	// Big 4
	Wave();
	Wave(const Wave&) = delete;
	Wave& operator = (const Wave&) = delete;
	virtual ~Wave();

	void SetPending(const char* const pWaveName, Wave::ID wave_id, Internal_FileCB_Command* pFileCommand);
	void SetPending(const char* const pWaveName, Wave::ID wave_id, UserAsyncLoadCallBack* pUserAsyncLoadCB);

	void SetId(Wave::ID id);
	Wave::ID GetId() const;

	void Register(WAVEFORMATEXTENSIBLE* poWfx, RawData* pRawDataBuff, unsigned long rawBuffSize);
	void AsyncRegister(WAVEFORMATEXTENSIBLE* poWfx, RawData* pRawDataBuff, unsigned long rawBuffSize);

	void Dump();
	void Wash();

	virtual bool Compare(DLink* pTargetNode) override;

private:
	void Clear();
	void LoadBuffer(const char* const pWaveName);
	void SetName(const char* const pWaveName);

public:
	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------

	WAVEFORMATEXTENSIBLE* poWfx;
	RawData* poRawBuff;
	unsigned long           rawBuffSize;
	ID                      id;
	char                    strName[NAME_SIZE];
	Internal_FileCB_Command* pIFileCB;
	UserAsyncLoadCallBack* pUserAsyncLoadCallback;
	Status status;
	Handle handle;
};
#endif // !WAVE_H