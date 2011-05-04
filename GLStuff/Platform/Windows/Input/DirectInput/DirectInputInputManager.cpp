#include "DirectInputInputManager.h"
#include <Common/GeexEngineException.h>

DirectInputInputManager::DirectInputInputManager(Win32Window* forWindow)
    : din(NULL),
    mouse(NULL),
    keyboard(NULL),
    InputManager()
{
    DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&din, NULL);

    if(!din)
        throw new GeexEngineException("Error creating DirectInput context");

    mouse = new DirectInputMouseInputDevice(din, forWindow->GetWindowHandle());
    mouse->Create();

    keyboard = new DirectInputKeyboardInputDevice(din, forWindow->GetWindowHandle());
    keyboard->Create();
}

DirectInputInputManager::~DirectInputInputManager()
{
    if(mouse)
    {
        delete mouse;
        mouse = NULL;
    }

    if(keyboard)
    {
        delete keyboard;
        keyboard = NULL;
    }

    if(din)
    {
        din->Release();
        din = NULL;
    }
}
