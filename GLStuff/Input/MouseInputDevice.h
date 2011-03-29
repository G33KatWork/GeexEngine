#ifndef _MOUSEINPUTDEVICE_H_
#define _MOUSEINPUTDEVICE_H_

#include <Input/InputDevice.h>
#include <Input/Keycodes.h>

class MouseInputDevice : public InputDevice
{
public:
	MouseInputDevice()
		: InputDevice() {}

	virtual ~MouseInputDevice() {}
	
	virtual long GetX() = 0;
	virtual long GetY() = 0;

	virtual long GetXDelta() = 0;
	virtual long GetYDelta() = 0;
	virtual long GetZDelta() = 0;

	//TODO: Buttonstate
	virtual bool GetButtonState(KeyCode key) = 0;
};

#endif
