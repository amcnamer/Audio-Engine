
#include "HandleMan.h"
#include "Handle.h"

Handle::Lock::Lock(const Handle& h)
	:handle(h),
	status(Lock::Status::UNLOCKED)
{
	this->lock();
}
Handle::Lock::~Lock()
{
	this->unlock();
}

Handle::Lock::operator bool() const
{
	return(this->status == Lock::Status::LOCKED);
}

void Handle::Lock::unlock()
{
	if (this->status == Lock::Status::LOCKED)
	{
		const Handle::Status h_status = Handle::ReleaseHandle(handle);
		if (h_status == Handle::Status::VALID_HANDLE)
		{
			this->status = Lock::Status::UNLOCKED;
		}
		else
		{
			this->status = Lock::Status::LOCKED;
		}
	}
	else
	{
		// already unlocked
		// do nothing
	}
}

void Handle::Lock::lock()
{
	if (this->status == Lock::Status::UNLOCKED)
	{
		const Handle::Status h_status = Handle::AcquireHandle(handle);
		if (h_status == Handle::Status::VALID_HANDLE)
		{
			this->status = Lock::Status::LOCKED;
		}
		else
		{
			this->status = Lock::Status::UNLOCKED;
		}
	}
	else
	{
		// already locked  --> should not happen
		assert(false);
	}
}

Handle::Lock::operator Handle::Status() const
{
	Handle::Status h_status;
	if (this->status == Lock::Status::LOCKED)
	{
		h_status = Handle::Status::SUCCESS;
	}
	else
	{
		h_status = Handle::Status::HANDLE_ERROR;
	}
	return h_status;
}
