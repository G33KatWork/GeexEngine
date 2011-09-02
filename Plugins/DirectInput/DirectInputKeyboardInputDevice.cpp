#include "DirectInputKeyboardInputDevice.h"

UCHAR keycodeConversion[256] =
{
	0x00,	//not existant (0x00)
	
	0x00,	//KEY_LBUTTON
	0x00,	//KEY_RBUTTON
	0x00,	//KEY_MBUTTON
	0x00,	//KEY_XBUTTON1
	0x00,	//KEY_XBUTTON2

	0x00,			//not existant (0x06)
	0x00,			//not existant (0x07)

	DIK_BACK,		//KEY_BACK
	DIK_TAB,		//KEY_BACK
	DIK_RETURN,		//KEY_RETURN
	DIK_PAUSE,		//KEY_PAUSE
	DIK_CAPITAL,	//KEY_CAPITAL
	DIK_ESCAPE,		//KEY_ESCAPE
	DIK_SPACE,		//KEY_SPACE
	DIK_PRIOR,		//KEY_PRIOR
	DIK_NEXT,		//KEY_NEXT
	DIK_END,		//KEY_END
	DIK_HOME,		//KEY_HOME
	DIK_LEFT,		//KEY_LEFT
	DIK_UP,			//KEY_UP
	DIK_RIGHT,		//KEY_RIGHT
	DIK_DOWN,		//KEY_DOWN
	0x00,			//KEY_PRINT
	DIK_INSERT,		//KEY_INSERT
	DIK_DELETE,		//KEY_DELETE
	DIK_LWIN,		//KEY_LWIN
	DIK_RWIN,		//KEY_RWIN
	DIK_NUMLOCK,	//KEY_NUMLOCK
	DIK_SCROLL,		//KEY_SCROLL
	DIK_LSHIFT,		//KEY_LSHIFT
	DIK_RSHIFT,		//KEY_RSHIFT
	DIK_LCONTROL,	//KEY_LCONTROL
	DIK_RCONTROL,	//KEY_RCONTROL
	DIK_LMENU,		//KEY_LMENU
	DIK_RMENU,		//KEY_RMENU

	DIK_GRAVE,		//KEY_GRAVE
	DIK_APOSTROPHE, //KEY_APOSTROPHE
	DIK_SEMICOLON,	//KEY_SEMICOLON
	DIK_LBRACKET,	//KEY_LBRACKET
	DIK_RBRACKET,	//KEY_RBRACKET
	DIK_SLASH,		//KEY_SLASH
	DIK_BACKSLASH,	//KEY_BACKSLASH
	DIK_EQUALS,		//KEY_EQUALS
	DIK_COMMA,		//KEY_COMMA
	DIK_MINUS,		//KEY_MINUS
	DIK_PERIOD,		//KEY_PERIOD
	
	0x00,			//not existant (0x2F)
	
	DIK_0,			//KEY_KEY_0
	DIK_1,
	DIK_2,
	DIK_3,
	DIK_4,
	DIK_5,
	DIK_6,
	DIK_7,
	DIK_8,
	DIK_9,
	
	0x00,			//not existant (0x3A)
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,			//not existant (0x40)

	DIK_A,			//KEY_KEY_A
	DIK_B,
	DIK_C,
	DIK_D,
	DIK_E,
	DIK_F,
	DIK_G,
	DIK_H,
	DIK_I,
	DIK_J,
	DIK_K,
	DIK_L,
	DIK_M,
	DIK_N,
	DIK_O,
	DIK_P,
	DIK_Q,
	DIK_R,
	DIK_S,
	DIK_T,
	DIK_U,
	DIK_V,
	DIK_W,
	DIK_X,
	DIK_Y,
	DIK_Z,			//KEY_KEY_z

	0x00,			//not existant (0x5B)
	0x00,			//not existant (0x5C)
	0x00,			//not existant (0x5D)
	0x00,			//not existant (0x5E)
	0x00,			//not existant (0x5F)

	DIK_NUMPAD0,	//KEY_NUMPAD0
	DIK_NUMPAD1,
	DIK_NUMPAD2,
	DIK_NUMPAD3,
	DIK_NUMPAD4,
	DIK_NUMPAD5,
	DIK_NUMPAD6,
	DIK_NUMPAD7,
	DIK_NUMPAD8,
	DIK_NUMPAD9,
	DIK_MULTIPLY,
	DIK_ADD,
	DIK_SUBTRACT,
	DIK_DECIMAL,
	DIK_DIVIDE,

	0x00,			//not existant (0x6F)

	DIK_F1,
	DIK_F2,
	DIK_F3,
	DIK_F4,
	DIK_F5,
	DIK_F6,
	DIK_F7,
	DIK_F8,
	DIK_F9,
	DIK_F10,
	DIK_F11,
	DIK_F12,

	0x00,
	//rest fills up with 0 (hopefully ;) )
};

DirectInputKeyboardInputDevice::DirectInputKeyboardInputDevice(LPDIRECTINPUT8 directInput, HWND windowHandle)
	: KeyboardInputDevice(),
	di(directInput),
	window(windowHandle)
{
	keyboardDevice = NULL;
	memset(&keyState, 0, sizeof(UCHAR[256]));
}

DirectInputKeyboardInputDevice::~DirectInputKeyboardInputDevice()
{
	Destroy();
}

void DirectInputKeyboardInputDevice::Create()
{
	if(!di)
		return;	//FIXME: throw exception

	Destroy();

	if(FAILED(di->CreateDevice(GUID_SysKeyboard, &keyboardDevice, NULL)))
		return;	//FIXME: throw exception

	if(FAILED(keyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
		return;	//FIXME: throw exception

	if(FAILED(keyboardDevice->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return; //FIXME: throw exception;

	if(FAILED(keyboardDevice->Acquire()))
		return; //FIXME: throw exception;
}

void DirectInputKeyboardInputDevice::Destroy()
{
	if(keyboardDevice)
	{
		keyboardDevice->Unacquire();
		keyboardDevice->Release();
		keyboardDevice = NULL;
	}
}

void DirectInputKeyboardInputDevice::Update()
{
	if(!keyboardDevice)
		return;

	HRESULT hr = keyboardDevice->GetDeviceState(sizeof(UCHAR[256]), &keyState);
	if(hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
	{
		if(FAILED(keyboardDevice->Acquire()))
		{
			return; //FIXME: throw error?
		}
	}
}

bool DirectInputKeyboardInputDevice::KeyPressed(KeyCode key)
{
	if(keycodeConversion[key] == 0x00)
		return false;
	
	return (keyState[keycodeConversion[key]] & 0x80) != 0;
}
