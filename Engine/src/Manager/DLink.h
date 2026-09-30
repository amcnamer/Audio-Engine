//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DLINK_H
#define DLINK_H

class DLink
{
public:
	DLink();

	// Becomes optional with a virtual with default implementation
	virtual char* GetObjName();

	// Abstract methods - must be implemented
	virtual void Wash() = 0;
	virtual bool Compare(DLink* pTargetNode) = 0;

	void Clear();
	virtual void Dump();


	// Data: -----------------------------
	DLink* pNext;
	DLink* pPrev;

};


#endif

// --- End of File ---
