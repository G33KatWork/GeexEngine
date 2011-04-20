#include <Platform/Windows/WindowsOpenGLApplication.h>

#include <Platform/Windows/Win32Window.h>
#include <3D/Rendering/OpenGL/WGLRenderer.h>
#include <Timing/Windows/WindowsTiming.h>
#include <Input/DirectInput/DirectInputInputManager.h>

#include <Common/GeexEngineException.h>

Renderer* WindowsOpenGLApplication::CreateRenderer(Window* forWindow)
{
    Renderer* r = new WGLRenderer(((Win32Window*)forWindow)->GetWindowHandle(), forWindow->GetWidth(), forWindow->GetHeight());

    if(glewInit() != GLEW_OK)
        throw new GeexEngineException("GLEW initialization failed");
    
    return r;
}

Window* WindowsOpenGLApplication::CreateRenderWindow()
{
    return new Win32Window("GeeXengine OpenGL Window", 0, 0, 640, 480);
}

TimingInformation* WindowsOpenGLApplication::CreateTimer()
{
    return new WindowsTiming();
}

InputManager* WindowsOpenGLApplication::CreateInputDevices(Window* forWindow)
{
    return new DirectInputInputManager((Win32Window*)forWindow);
}
