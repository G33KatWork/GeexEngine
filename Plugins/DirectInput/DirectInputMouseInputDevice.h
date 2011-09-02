#ifndef _DIMOUSEINPUTDEVICE_H_
#define _DIMOUSEINPUTDEVICE_H_

#include <Input/MouseInputDevice.h>

#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>

class DirectInputMouseInputDevice : public MouseInputDevice
{
private:
	LPDIRECTINPUT8 di;
	HWND window;

	LPDIRECTINPUTDEVICE8 mouseDevice;

	DIMOUSESTATE2 mouseState;
	POINT cursorPos;

public:
	DirectInputMouseInputDevice(LPDIRECTINPUT8 directInput, HWND windowHandle);
	virtual ~DirectInputMouseInputDevice();

	virtual void Create();
	virtual void Destroy();
	virtual void Update();

	virtual long GetX() { return cursorPos.x; }
	virtual long GetY() { return cursorPos.y; }

	virtual long GetXDelta() { return mouseState.lX; }
	virtual long GetYDelta() { return mouseState.lY; }
	virtual long GetZDelta() { return mouseState.lZ; }

	virtual bool GetButtonState(KeyCode key);
};

#endif
