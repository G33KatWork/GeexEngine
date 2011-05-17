#ifndef _WINOGL_APPLICATION_H_
#define _WINOGL_APPLICATION_H_

#include <Common/GeexEngineExports.h>

#include <Platform/Application.h>

class GEEXENGINE_API WindowsOpenGLApplication : public Application
{
public:
    virtual ~WindowsOpenGLApplication() {}

protected:
    WindowsOpenGLApplication()
        : Application()
    { }

	virtual Renderer* CreateRenderer(Window* forWindow);
	virtual Window* CreateRenderWindow();
	virtual TimingInformation* CreateTimer();
    virtual InputManager* CreateInputDevices(Window* forWindow);
};

#endif
