#ifndef _TESTAPPLICATION_H_
#define _TESTAPPLICATION_H_

#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>

#include <Application.h>
#include <Input/DirectInput/DirectInputMouseInputDevice.h>
#include <Input/DirectInput/DirectInputKeyboardInputDevice.h>
#include <3D/PerspectiveCamera.h>

class TestApplication : public Application
{
public:
    TestApplication();

    virtual bool OnInitialize();
    virtual void OnUpdate();
    virtual void OnRedraw();
    virtual void OnTerminate();

protected:
    virtual Renderer* CreateRenderer(Window* forWindow);
    virtual Window* CreateRenderWindow();
    virtual TimingInformation* CreateTimer();
    virtual void CreateInputDevices(Window* forWindow);

    LPDIRECTINPUT8 din;
    MouseInputDevice* mouse;
    KeyboardInputDevice* keyboard;
};

#endif