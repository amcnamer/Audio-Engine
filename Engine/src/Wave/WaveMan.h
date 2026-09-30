//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef WAVE_MAN_H
#define WAVE_MAN_H 

#include "ManBase.h"
#include "DLinkMan.h"
#include "Wave.h"
#include "Internal_FileCB_Command.h"
#include "UserAsyncLoadCallBack.h"


class WaveMan : public ManBase
{

	//----------------------------------------------------------------------
	// Constructor
	//----------------------------------------------------------------------
private:
	WaveMan(int reserveNum = 3, int reserveGrow = 1);
	WaveMan() = delete;
	WaveMan(const WaveMan&) = delete;
	WaveMan& operator = (const WaveMan&) = delete;
	~WaveMan();

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static Wave* Add(Wave::ID id, const char* const pWaveName, UserAsyncLoadCallBack* pUserAsyncLoadCallback);
	static Wave* Add(Wave::ID id, const char* const pWaveName, Internal_FileCB_Command* pIFileCB);

	static Wave* Find(Wave::ID id);

	static void Remove(Wave* pNode);
	static void RemoveAll(Internal_FileCB_Command* pIFileCB);

	static void Dump();

	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
private:
	static WaveMan* GetInstance();

	//----------------------------------------------------------------------
	// Override Abstract methods
	//----------------------------------------------------------------------
protected:
	DLink* derivedCreateNode() override;


	//----------------------------------------------------------------------
	// Data: unique data for this manager 
	//----------------------------------------------------------------------
private:
	Wave* poNodeCompare;
	static WaveMan* psInstance;

};


#endif