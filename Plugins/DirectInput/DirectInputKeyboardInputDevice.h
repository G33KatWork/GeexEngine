#ifndef _DIKEYBOARDINPUTDEVICE_H_
#define _DIKEYBOARDINPUTDEVICE_H_

#include <Input/KeyboardInputDevice.h>

#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>

class DirectInputKeyboardInputDevice : public KeyboardInputDevice
{
private:
	LPDIRECTINPUT8 di;
	HWND window;
	UCHAR keyState[256];

	LPDIRECTINPUTDEVICE8 keyboardDevice;

public:
	DirectInputKeyboardInputDevice(LPDIRECTINPUT8 directInput, HWND windowHandle);
	virtual ~DirectInputKeyboardInputDevice();

	virtual void Create();
	virtual void Destroy();
	virtual void Update();

	virtual bool KeyPressed(KeyCode key);
};

#endif
