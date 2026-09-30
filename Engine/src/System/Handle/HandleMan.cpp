#include "HandleMan.h"

HandleMan* HandleMan::pInstance = nullptr;
HandleMan::Ready HandleMan::ready = HandleMan::Ready::UNINITIALIZED;

void HandleMan::Create()
{
	HandleMan::pInstance = new HandleMan();
	HandleMan::ready = HandleMan::Ready::INITIALIZED;
}

void HandleMan::Destroy()
{
	delete HandleMan::pInstance;
	HandleMan::pInstance = nullptr;
	HandleMan::ready = HandleMan::Ready::DESTROYED;
}

HandleMan::HandleMan()
{
	this->srcID = STARTING_ID;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		this->table[i].id.store(INVALID_STATE);
	}
}

HandleMan::~HandleMan()
{
	this->srcID = STARTING_ID;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		this->table[i].id.store(INVALID_STATE);
	}
}

HandleMan::Ready HandleMan::GetReadyStatus()
{
	return HandleMan::ready;
}


Handle::Status HandleMan::InvalidateHandle(const Handle& handle)
{
	HandleMan* pMan = HandleMan::GetInstance();
	assert(pMan);

	// Is Range and ID valid?
	Handle::Status status = pMan->IsHandleAndRangeValid(handle);

	if (status == Handle::Status::VALID_HANDLE)
	{
		// Block until you get the exclusive lock
		pMan->table[handle.GetIndex()].mtx.lock();

		// ---------------------------------------------------------------------
		// Race condition:
		// What happens if the ID is invalidated between the test and the lock?
		// ---------------------------------------------------------------------

			// Is ID valid?
		status = pMan->IsHandleAndRangeValid(handle);

		if (status == Handle::Status::VALID_HANDLE)
		{
			// nuke it
			pMan->table[handle.GetIndex()].id.store(INVALID_STATE);

			// release the mtx
			pMan->table[handle.GetIndex()].mtx.unlock();

			status = Handle::Status::INVALID_HANDLE;
		}
		else if (status == Handle::Status::INVALID_HANDLE)
		{
			// race condition... handle is invalid - status is ERROR

			// release the mtx
			pMan->table[handle.GetIndex()].mtx.unlock();
		}
		else
		{
			// Something bad happened
			assert(false);
			status = Handle::Status::HANDLE_ERROR;
		}
	}
	else if (status == Handle::Status::INVALID_HANDLE)
	{
		// its already invalidated
	}
	else
	{
		// Something bad happened
		assert(false);
		status = Handle::Status::HANDLE_ERROR;
	}

	return status;
}

Handle::Status HandleMan::IsValid(const Handle& handle)
{
	HandleMan* pMan = HandleMan::GetInstance();
	assert(pMan);

	Handle::Status status = pMan->IsHandleAndRangeValid(handle);
	return status;
}

Handle::Status HandleMan::IsValidAcquire(const Handle& handle)
{
	HandleMan* pMan = HandleMan::GetInstance();
	assert(pMan);

	// is it valid?
	Handle::Status status = pMan->IsHandleAndRangeValid(handle);

	if (status == Handle::Status::VALID_HANDLE)
	{
		// get shared mutex
		pMan->table[handle.GetIndex()].mtx.lock_shared();

		// Double check... in case of Race condition
		status = pMan->IsHandleAndRangeValid(handle);

		if (status == Handle::Status::VALID_HANDLE)
		{
			// all good!
		}
		else
		{
			// not valid... 
			// so unlock it
			pMan->table[handle.GetIndex()].mtx.unlock_shared();
		}

	}

	return status;
}

Handle::Status HandleMan::IsValidRelease(const Handle& handle)
{
	HandleMan* pMan = HandleMan::GetInstance();
	assert(pMan);

	// is it valid?
	Handle::Status status = pMan->IsHandleAndRangeValid(handle);

	if (status == Handle::Status::VALID_HANDLE)
	{
		// get shared mutex
		pMan->table[handle.GetIndex()].mtx.unlock_shared();
	}
	else
	{
		// Something bad has happened...
		assert(false);
	}

	return status;
}

Handle::Status HandleMan::ActivateHandle(Handle::ID& new_id, Handle::Index& index)
{
	HandleMan* pMan = HandleMan::GetInstance();
	assert(pMan);

	Handle::Status 	status = Handle::Status::HANDLE_ERROR;

	if (pMan->FindNextAvailable(index))
	{
		// Block until you get the exclusive lock
		pMan->table[index].mtx.lock();

		// ---------------------------------------------------------------------
		// Race condition:
		// What happens if the ID is invalidated between the test and the lock?
		// ---------------------------------------------------------------------
		if (pMan->table[index].id.load() != PENDING_STATE)
		{
			// unlock
			pMan->table[index].mtx.unlock();

			// bail and fall through
			status = Handle::Status::HANDLE_ERROR;

			assert(false);
		}
		else
		{
			// Set it - atomic!
			new_id = pMan->GetNewID();
			pMan->table[index].id.store(new_id);

			// unlock
			pMan->table[index].mtx.unlock();

			status = Handle::Status::VALID_HANDLE;
		}
	}
	else
	{
		status = Handle::Status::INSUFFICIENT_SPACE;
	}

	return status;
}

void HandleMan::PrintTable()
{
	HandleMan* pMan = HandleMan::GetInstance();
	assert(pMan);

	std::lock_guard<std::mutex> lock(pMan->tableMtx);
	{
		Trace::out("\n");

		// No protection.... Just printing
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (pMan->table[i].id == INVALID_STATE)
			{
				Trace::out("[%d]: %s \n", i, STRING_ME(INVALID_STATE));
			}
			else
			{
				Trace::out("[%d]: %x \n", i, pMan->table[i].id.load());
			}
		}

		Trace::out("\n");
	}
}

HandleMan* HandleMan::GetInstance()
{
	HandleMan* psInstance = nullptr;
	if (HandleMan::pInstance)
	{
		psInstance = HandleMan::pInstance;
	}
	
	return psInstance;
}

Handle::ID HandleMan::GetNewID()
{
	std::lock_guard<std::mutex> lock(this->tableMtx);

	// Increment
	this->srcID++;

	// make sure the number is never colliding with our reserved state
	//          PENDING_STATE
	//          INVALID_STATE
	while (this->srcID == HandleMan::INVALID_STATE || this->srcID == HandleMan::PENDING_STATE)
	{
		this->srcID++;
	}

	return this->srcID;
}

bool HandleMan::FindNextAvailable(Handle::Index& index)
{
	std::lock_guard<std::mutex> lock(this->tableMtx);

	bool status = false;

	for (Handle::Index i = 0; i < TABLE_SIZE; i++)
	{
		//          contained(id)    expected(invalid)  val(pending)
		//  if contain == expected  (id == INVALID_STATE)
		//         contain = val
		//         id <-- PENDING_STATE
		//         return true
		//  else  // contain != expected  (id != INVALID_STATE)
		//         contained = expected
		//         expected <-- id (which by logic isn't INVALID_STATE 
		//                          so itst PENDING or something valid)
		//         return false

		// atomic exchange
		unsigned int expected = HandleMan::INVALID_STATE;
		if (this->table[i].id.compare_exchange_strong(expected, HandleMan::PENDING_STATE))
		{
			// found one
			index = i;
			status = true;
			break;
		}
	}

	return status;
}

Handle::Status HandleMan::IsHandleAndRangeValid(const Handle& handle)
{
	Handle::Status status = Handle::Status::HANDLE_ERROR;
	if (handle.GetIndex() < TABLE_SIZE)
	{
		if (this->table[handle.GetIndex()].id.load() == handle.GetID())
		{
			status = Handle::Status::VALID_HANDLE;
		}
		else
		{
			status = Handle::Status::INVALID_HANDLE;
		}
	}
	else
	{
		status = Handle::Status::HANDLE_ERROR;
	}
	return status;
}

