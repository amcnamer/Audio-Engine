

#include "Handle.h"
#include "HandleMan.h"

Handle::Handle()
{
	//Activate Handle
	Status status = Handle::Status::NOT_INITIALIZE;

	unsigned int count = Handle::NUM_RETRY;

	while (count--)
	{
		status = Handle::ActivateHandle(*this);
		if (status == Handle::Status::VALID_HANDLE)
		{
			status = Status::SUCCESS;
			break;
		}
	}

	assert(status == Status::SUCCESS);
}

Handle::~Handle()
{
	//Invalidate Handle
	Status status = Handle::Status::NOT_INITIALIZE;
	unsigned int count = Handle::NUM_RETRY;

	while (count--)
	{
		status = HandleMan::InvalidateHandle(*this);
		if (status == Handle::Status::INVALID_HANDLE)
		{
			break;
		}
	}
	assert(status == Handle::Status::INVALID_HANDLE);
}

Handle::Status Handle::ActivateHandle(Handle& handle)
{
	//Activate
	Status status = HandleMan::ActivateHandle(handle.id, handle.index);

	return status;
}

Handle::ID Handle::GetID() const
{
	return this->id;
}

Handle::Index Handle::GetIndex() const
{
	return this->index;
}

//Tunneling Functions
Handle::Status Handle::IsValid(const Handle& handle)
{
	return HandleMan::IsValid(handle);
}

Handle::Status Handle::InvalidateHandle(const Handle& handle)
{
	return HandleMan::InvalidateHandle(handle);
}

Handle::Status Handle::AcquireHandle(const Handle& handle)
{
	return HandleMan::IsValidAcquire(handle);
}

Handle::Status Handle::ReleaseHandle(const Handle& handle)
{
	return HandleMan::IsValidRelease(handle);
}
