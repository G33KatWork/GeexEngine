#ifndef _WINDX9_APPLICATION_H_
#define _WINDX9_APPLICATION_H_

#include <Platform/Application.h>

class WindowsDirectXApplication : public Application
{
public:
    virtual ~WindowsDirectXApplication() {}

protected:
    WindowsDirectXApplication()
        : Application()
    { }

	virtual Renderer* CreateRenderer(Window* forWindow);
	virtual Window* CreateRenderWindow();
	virtual TimingInformation* CreateTimer();
    virtual InputManager* CreateInputDevices(Window* forWindow);
};

#endif
