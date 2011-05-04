#ifndef _KEYCODES_H_
#define _KEYCODES_H_

//Borrowed from Irrlicht engine
enum KeyCode
	{
		KEY_LBUTTON          = 0x01,  // Left mouse button
		KEY_RBUTTON          = 0x02,  // Right mouse button
		KEY_MBUTTON          = 0x03,  // Middle mouse button (three-button mouse)
		KEY_XBUTTON1         = 0x04,  // Windows 2000/XP: X1 mouse button
		KEY_XBUTTON2         = 0x05,  // Windows 2000/XP: X2 mouse button
		
		KEY_BACK             = 0x08,  // BACKSPACE key
		KEY_TAB              = 0x09,  // TAB key
		KEY_RETURN           = 0x0A,  // ENTER key
		KEY_PAUSE            = 0x0B,  // PAUSE key
		KEY_CAPITAL          = 0x0C,  // CAPS LOCK key
		KEY_ESCAPE           = 0x0D,  // ESC key
		KEY_SPACE            = 0x0E,  // SPACEBAR
		KEY_PRIOR            = 0x0F,  // PAGE UP key
		KEY_NEXT             = 0x10,  // PAGE DOWN key
		KEY_END              = 0x11,  // END key
		KEY_HOME             = 0x12,  // HOME key
		KEY_LEFT             = 0x13,  // LEFT ARROW key
		KEY_UP               = 0x14,  // UP ARROW key
		KEY_RIGHT            = 0x15,  // RIGHT ARROW key
		KEY_DOWN             = 0x16,  // DOWN ARROW key
		KEY_PRINT            = 0x17,  // PRINT key
		KEY_INSERT           = 0x18,  // INS key
		KEY_DELETE           = 0x19,  // DEL key
		KEY_LWIN             = 0x1A,  // Left Windows key (Microsoft® Natural® keyboard)
		KEY_RWIN             = 0x1B,  // Right Windows key (Natural keyboard)
		KEY_NUMLOCK          = 0x1C,  // NUM LOCK key
		KEY_SCROLL           = 0x1D,  // SCROLL LOCK key
		KEY_LSHIFT           = 0x1E,  // Left SHIFT key
		KEY_RSHIFT           = 0x1F,  // Right SHIFT key
		KEY_LCONTROL         = 0x20,  // Left CONTROL key
		KEY_RCONTROL         = 0x21,  // Right CONTROL key
		KEY_LMENU            = 0x22,  // Left MENU key
		KEY_RMENU            = 0x23,  // Right MENU key
		
		KEY_GRAVE            = 0x24,  // Acongrave Key (`)
		KEY_APOSTROPHE       = 0x25,  // Apostrophe Key (')
		KEY_SEMICOLON        = 0x26,  // Semicolon Key (;)
		KEY_LBRACKET         = 0x27,  // Left bracket ([)
		KEY_RBRACKET		 = 0x28,  // Right bracket (])
		KEY_SLASH			 = 0x29,  // Slash Key  (/)
		KEY_BACKSLASH		 = 0x2A,  // Backslash Key (\)
		KEY_EQUALS           = 0x2B,  // Equal Key  (=)
		KEY_COMMA            = 0x2C,  // Comma Key  (,)
		KEY_MINUS            = 0x2D,  // Minus Key  (-)
		KEY_PERIOD           = 0x2E,  // Period Key (.)

		KEY_KEY_0            = 0x30,  // 0 key
		KEY_KEY_1            = 0x31,  // 1 key
		KEY_KEY_2            = 0x32,  // 2 key
		KEY_KEY_3            = 0x33,  // 3 key
		KEY_KEY_4            = 0x34,  // 4 key
		KEY_KEY_5            = 0x35,  // 5 key
		KEY_KEY_6            = 0x36,  // 6 key
		KEY_KEY_7            = 0x37,  // 7 key
		KEY_KEY_8            = 0x38,  // 8 key
		KEY_KEY_9            = 0x39,  // 9 key

		KEY_KEY_A            = 0x41,  // A key
		KEY_KEY_B            = 0x42,  // B key
		KEY_KEY_C            = 0x43,  // C key
		KEY_KEY_D            = 0x44,  // D key
		KEY_KEY_E            = 0x45,  // E key
		KEY_KEY_F            = 0x46,  // F key
		KEY_KEY_G            = 0x47,  // G key
		KEY_KEY_H            = 0x48,  // H key
		KEY_KEY_I            = 0x49,  // I key
		KEY_KEY_J            = 0x4A,  // J key
		KEY_KEY_K            = 0x4B,  // K key
		KEY_KEY_L            = 0x4C,  // L key
		KEY_KEY_M            = 0x4D,  // M key
		KEY_KEY_N            = 0x4E,  // N key
		KEY_KEY_O            = 0x4F,  // O key
		KEY_KEY_P            = 0x50,  // P key
		KEY_KEY_Q            = 0x51,  // Q key
		KEY_KEY_R            = 0x52,  // R key
		KEY_KEY_S            = 0x53,  // S key
		KEY_KEY_T            = 0x54,  // T key
		KEY_KEY_U            = 0x55,  // U key
		KEY_KEY_V            = 0x56,  // V key
		KEY_KEY_W            = 0x57,  // W key
		KEY_KEY_X            = 0x58,  // X key
		KEY_KEY_Y            = 0x59,  // Y key
		KEY_KEY_Z            = 0x5A,  // Z key

		KEY_NUMPAD0          = 0x60,  // Numeric keypad 0 key
		KEY_NUMPAD1          = 0x61,  // Numeric keypad 1 key
		KEY_NUMPAD2          = 0x62,  // Numeric keypad 2 key
		KEY_NUMPAD3          = 0x63,  // Numeric keypad 3 key
		KEY_NUMPAD4          = 0x64,  // Numeric keypad 4 key
		KEY_NUMPAD5          = 0x65,  // Numeric keypad 5 key
		KEY_NUMPAD6          = 0x66,  // Numeric keypad 6 key
		KEY_NUMPAD7          = 0x67,  // Numeric keypad 7 key
		KEY_NUMPAD8          = 0x68,  // Numeric keypad 8 key
		KEY_NUMPAD9          = 0x69,  // Numeric keypad 9 key
		KEY_MULTIPLY         = 0x6A,  // Multiply key
		KEY_ADD              = 0x6B,  // Add key
		KEY_SUBTRACT         = 0x6C,  // Subtract key
		KEY_DECIMAL          = 0x6D,  // Decimal key
		KEY_DIVIDE           = 0x6E,  // Divide key
		
		KEY_F1               = 0x70,  // F1 key
		KEY_F2               = 0x71,  // F2 key
		KEY_F3               = 0x72,  // F3 key
		KEY_F4               = 0x73,  // F4 key
		KEY_F5               = 0x74,  // F5 key
		KEY_F6               = 0x75,  // F6 key
		KEY_F7               = 0x76,  // F7 key
		KEY_F8               = 0x77,  // F8 key
		KEY_F9               = 0x78,  // F9 key
		KEY_F10              = 0x79,  // F10 key
		KEY_F11              = 0x7A,  // F11 key
		KEY_F12              = 0x7B,  // F12 key
		
		KEY_KEY_CODES_COUNT  = 0xFF // this is not a key, but the amount of keycodes there are.
	};

#endif
