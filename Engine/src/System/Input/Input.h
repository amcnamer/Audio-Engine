//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef KEY_BOARD_H
#define KEY_BOARD_H

#include "Engine.h"
#include "MathEngine.h"

namespace Azul
{
	enum class KeyBoard
	{
		Key_A = 'A',
		Key_B = 'B',
		Key_C = 'C',
		Key_D = 'D',
		Key_E = 'E',
		Key_F = 'F',
		Key_G = 'G',
		Key_H = 'H',
		Key_I = 'I',
		Key_J = 'J',
		Key_K = 'K',
		Key_L = 'L',
		Key_M = 'M',
		Key_N = 'N',
		Key_O = 'O',
		Key_P = 'P',
		Key_Q = 'Q',
		Key_R = 'R',
		Key_S = 'S',
		Key_T = 'T',
		Key_U = 'U',
		Key_V = 'V',
		Key_W = 'W',
		Key_X = 'X',
		Key_Y = 'Y',
		Key_Z = 'Z',
		Key_0 = '0',
		Key_1 = '1',
		Key_2 = '2',
		Key_3 = '3',
		Key_4 = '4',
		Key_5 = '5',
		Key_6 = '6',
		Key_7 = '7',
		Key_8 = '8',
		Key_9 = '9',
		Key_ESCAPE = VK_ESCAPE,
		Key_SPACE = VK_SPACE,
		Key_LEFT = VK_LEFT,
		Key_UP = VK_UP,
		Key_RIGHT = VK_RIGHT,
		Key_DOWN = VK_DOWN
	};

	class Input
	{
	public:
		static bool GetKeyPress(KeyBoard key);

	};
}

#endif

// --- End of File ---

