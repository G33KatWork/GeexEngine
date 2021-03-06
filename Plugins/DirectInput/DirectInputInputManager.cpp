#include "DirectInputInputManager.h"
#include <Common/GeexEngineException.h>
#include <Plugins/Interface.h>

REGISTER_INTERFACE_ARG1(DirectInputInputManager, InputManager, "Input", Window*);

DirectInputInputManager::DirectInputInputManager(Window* forWindow)
    : din(NULL),
    mouse(NULL),
    keyboard(NULL),
    InputManager()
{
    DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&din, NULL);

    if(!din)
        throw GeexEngineException("Error creating DirectInput context");

    HWND windowHandle = FindWindow("GeexEngineWindow", forWindow->GetTitle());
    if(!windowHandle)
        throw GeexEngineException("Main window handle couldn't be retrieved");

    mouse = new DirectInputMouseInputDevice(din, windowHandle);
    mouse->Create();

    keyboard = new DirectInputKeyboardInputDevice(din, windowHandle);
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
