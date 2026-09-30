
#ifndef ASOUND_MAN_H
#define ASOUND_MAN_H 

#include "ManBase.h"
#include "DLinkMan.h"
#include "Sound.h"
#include "ASound.h"

class ASoundMan : public ManBase
{

	//----------------------------------------------------------------------
	// Constructor
	//----------------------------------------------------------------------
private:
	ASoundMan(int reserveNum = 3, int reserveGrow = 1);
	ASoundMan() = delete;
	ASoundMan(const ASoundMan&) = delete;
	ASoundMan& operator = (const ASoundMan&) = delete;
	~ASoundMan();

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static ASound* Add(Sound::ID snd_id, Sound* pSnd);
	static ASound* Find(Sound::ID snd_id);

	static void Remove(ASound* pNode);
	static void Dump();

	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
private:
	static ASoundMan* GetInstance();

	//----------------------------------------------------------------------
	// Override Abstract methods
	//----------------------------------------------------------------------
protected:
	DLink* derivedCreateNode() override;


	//----------------------------------------------------------------------
	// Data: unique data for this manager 
	//----------------------------------------------------------------------
private:
	ASound* poNodeCompare;
	static ASoundMan* pInstance;

};


#endif