#ifndef HANDLE_MAN_H
#define HANDLE_MAN_H

#include <shared_mutex>
#include "Handle.h"

class HandleMan
{
public:
	enum class Ready
	{
		UNINITIALIZED,
		INITIALIZED,
		DESTROYED
	};
private:
	static const unsigned int TABLE_SIZE = 256;
	static const unsigned int INVALID_STATE = 0x0;
	static const unsigned int PENDING_STATE = 0xFFFFFFFF;
	static const unsigned int STARTING_ID = 0xAAAA0000;

	class HandleTableEntry
	{
	public:
		HandleTableEntry() = default;
		HandleTableEntry(const HandleTableEntry&) = delete;
		HandleTableEntry& operator=(const HandleTableEntry) = delete;
		~HandleTableEntry() = default;

	public:
		std::atomic<unsigned int> id;
		std::shared_mutex		  mtx;
	};

public:
	static void Create();
	static void Destroy();
	static Ready GetReadyStatus();

	//Cannot copy singleton Manager
	HandleMan(const HandleMan&) = delete;
	const HandleMan& operator=(const HandleMan&) = delete;

	//strategically expose certain aspects of the class
	static Handle::Status IsValid(const Handle& handle);

	static Handle::Status IsValidAcquire(const Handle& handle);
	static Handle::Status IsValidRelease(const Handle& handle);

	static Handle::Status ActivateHandle(Handle::ID& id, Handle::Index& index);
	static Handle::Status InvalidateHandle(const Handle& handle);

	//debug print. Remove from application before release
	static void PrintTable();

private:
	HandleMan();
	~HandleMan();

	static HandleMan* GetInstance();
	static HandleMan* pInstance;
	static HandleMan::Ready ready;

	Handle::ID GetNewID();
	bool FindNextAvailable(Handle::Index& index);

	Handle::Status IsHandleAndRangeValid(const Handle& handle);

	HandleTableEntry table[TABLE_SIZE];
	Handle::ID srcID;
	std::mutex tableMtx;

};



#endif 
