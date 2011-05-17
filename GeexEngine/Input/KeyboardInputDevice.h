#ifndef _KEYBOARDINPUTDEVICE_H_
#define _KEYBOARDINPUTDEVICE_H_

#include <Common/GeexEngineExports.h>

#include <Input/InputDevice.h>
#include <Input/Keycodes.h>

class GEEXENGINE_API KeyboardInputDevice : public InputDevice
{
public:
	KeyboardInputDevice()
		: InputDevice() {}

	virtual ~KeyboardInputDevice() {}

	virtual bool KeyPressed(KeyCode key) = 0;
};

#endif
