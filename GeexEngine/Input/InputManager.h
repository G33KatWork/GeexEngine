#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include <Input/MouseInputDevice.h>
#include <Input/KeyboardInputDevice.h>

//TODO: Joysticks, keymaps, multiple mice and keyboards, etc.

class InputManager
{
public:
    virtual ~InputManager() {}

protected:
    InputManager() {}

public:
	virtual MouseInputDevice* GetMouse() = 0;
    virtual KeyboardInputDevice* GetKeyboard() = 0;

private:
    //prevent copying
    InputManager(const InputManager& other) {}
};

#endif
