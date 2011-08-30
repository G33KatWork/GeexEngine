#include <Platform/Windows/WindowsOpenGLApplication.h>

#include <Platform/Windows/Win32Window.h>
#include <Platform/Windows/Timing/WindowsTiming.h>
#include <Platform/Windows/Input/DirectInput/DirectInputInputManager.h>

#include <Common/GeexEngineException.h>

Renderer* WindowsOpenGLApplication::CreateRenderer(Window* forWindow)
{
    typedef Renderer* (*InstantiateRendererPtr)(Window* window, int width, int height);

    HMODULE oglRendererModule = LoadLibrary("OpenGLRenderer.dll");
    if(!oglRendererModule)
        throw GeexEngineException("Failed to load OpenGL renderer library");

    InstantiateRendererPtr InstantiateRenderer = (InstantiateRendererPtr)GetProcAddress(oglRendererModule, "InstantiateRenderer");
    if(!InstantiateRenderer)
        throw GeexEngineException("Renderer instantiation entrypoint was not found");

    //Renderer* r = new WGLRenderer(((Win32Window*)forWindow)->GetWindowHandle(), forWindow->GetWidth(), forWindow->GetHeight());
    Renderer* r = InstantiateRenderer(forWindow, forWindow->GetWidth(), forWindow->GetHeight());
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
