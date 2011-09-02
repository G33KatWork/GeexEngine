#ifndef _DI_INPUT_MANAGER_H_
#define _DI_INPUT_MANAGER_H_

#include <Input/InputManager.h>
#include <Platform/Window.h>

#include "DirectInputMouseInputDevice.h"
#include "DirectInputKeyboardInputDevice.h"

class DirectInputInputManager : public InputManager
{
public:
    DirectInputInputManager(Window* forWindow);
    virtual ~DirectInputInputManager();

    virtual MouseInputDevice* GetMouse() { return this->mouse; }
    virtual KeyboardInputDevice* GetKeyboard() { return this->keyboard; }

protected:
    LPDIRECTINPUT8 din;
    MouseInputDevice* mouse;
    KeyboardInputDevice* keyboard;

private:
    //prevent copying
    DirectInputInputManager(const DirectInputInputManager& other) {}
};

#endif
