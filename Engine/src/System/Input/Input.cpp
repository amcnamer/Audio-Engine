//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "Input.h"

namespace Azul
{
	bool Input::GetKeyPress(KeyBoard key)
	{
		bool status = false;
		if(GetKeyState((int)key) & 0x8000)
		{
			status = true;
		}

		return status;
	}

}

// --- End of File ---
