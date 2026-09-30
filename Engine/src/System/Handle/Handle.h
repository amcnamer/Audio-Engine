#ifndef HANDLE_H
#define HANDLE_H


class Handle
{
public:

	//number of attempts to acquire a handle for race condition
	static const unsigned int NUM_RETRY = 100;

	enum class Status
	{
		SUCCESS = 0x7EEE0000,

		INSUFFICIENT_SPACE,
		INVALID_HANDLE,
		VALID_HANDLE,

		NOT_INITIALIZE,

		HANDLE_ERROR = 0x7EEEFFFF

	};

	class Lock
	{
	public:
		enum class Status
		{
			LOCKED,
			UNLOCKED
		};

	public:
		Lock(const Handle& h);
		Lock() = delete;
		Lock(const Lock&) = delete;
		Lock& operator=(const Lock&) = delete;
		~Lock();

		//boolean operator
		operator bool() const;

		//manual lock and unlock
		void unlock();
		void lock();

		//conversion operator from Lock to Handle Status
		operator Handle::Status() const;

	private:
		const Handle& handle;
		Lock::Status status;

	};

	class LockTwoInput
	{
	public:
		enum class Status
		{
			LOCKED,
			UNLOCKED
		};
	public:
		LockTwoInput(Handle& this_handle, const Handle& input_handle);

		LockTwoInput() = delete;
		LockTwoInput(const LockTwoInput&) = delete;
		LockTwoInput& operator=(const LockTwoInput&) = delete;
		~LockTwoInput();

		operator bool() const;

		//manual lock and unlock
		void unlock();
		void lock();

		operator Handle::Status() const;

	private:
		Handle& this_handle; //no copy just a reference pointer to the original
		const Handle& input_handle; // same
		LockTwoInput::Status status;

	};

	#define CopyConstructorLock LockTwoInput
	#define AssignOperatorLock LockTwoInput

	typedef unsigned int ID;
	typedef unsigned int Index;

public:
	Handle();
	~Handle();

	//Cannot copy handles
	Handle(const Handle&) = delete;
	const Handle& operator= (const Handle&) = delete;

	//can look but not set Handles
	ID GetID() const;
	Index GetIndex() const;

	//Tunnel method to prevent dependency on HandleMan

	static Status IsValid(const Handle& handle);

	static Status ActivateHandle(Handle& handle);
	static Status InvalidateHandle(const Handle& handle);

	static Status AcquireHandle(const Handle& handle);
	static Status ReleaseHandle(const Handle& handle);

private:
	ID id;
	Index index;
};
#endif 
