#include <Platform/Windows/WindowsDirectXApplication.h>

#include <Platform/Windows/Win32Window.h>
#include <Platform/Windows/Timing/WindowsTiming.h>
#include <Platform/Windows/Input/DirectInput/DirectInputInputManager.h>

#include <Common/GeexEngineException.h>

Renderer* WindowsDirectXApplication::CreateRenderer(Window* forWindow)
{
    typedef Renderer* (*InstantiateRendererPtr)(Window* window, int width, int height);

    HMODULE oglRendererModule = LoadLibrary("DirectXRenderer.dll");
    if(!oglRendererModule)
        throw GeexEngineException("Failed to load DirectX renderer library");

    InstantiateRendererPtr InstantiateRenderer = (InstantiateRendererPtr)GetProcAddress(oglRendererModule, "InstantiateRenderer");
    if(!InstantiateRenderer)
        throw GeexEngineException("Renderer instantiation entrypoint was not found");

    //Renderer* r = new WGLRenderer(((Win32Window*)forWindow)->GetWindowHandle(), forWindow->GetWidth(), forWindow->GetHeight());
    Renderer* r = InstantiateRenderer(forWindow, forWindow->GetWidth(), forWindow->GetHeight());
    return r;
}

Window* WindowsDirectXApplication::CreateRenderWindow()
{
    return new Win32Window("GeeXengine DirectX Window", 0, 0, 640, 480);
}

TimingInformation* WindowsDirectXApplication::CreateTimer()
{
    return new WindowsTiming();
}

InputManager* WindowsDirectXApplication::CreateInputDevices(Window* forWindow)
{
    return new DirectInputInputManager((Win32Window*)forWindow);
}
