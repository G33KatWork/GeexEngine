#include <Platform/Windows/WindowsOpenGLApplication.h>
#include <Common/GeexEngineException.h>

Renderer* WindowsOpenGLApplication::CreateRenderer(Window* forWindow)
{
    IPlugin* rendererPlugin = pluginManager->Load("OpenGLRenderer");
    Renderer* renderer = (Renderer*)rendererPlugin->InstantiateInterface("Renderer", I_ARG(Window*, forWindow), I_ARG(int, forWindow->GetWidth()), I_ARG(int, forWindow->GetHeight()));

    if(!renderer)
        throw GeexEngineException("DirectXRenderer interface instantiation failed");

    return renderer;
}

Window* WindowsOpenGLApplication::CreateRenderWindow()
{
    IPlugin* platformPlugin = pluginManager->Load("Win32Platform");
    Window* window = (Window*)platformPlugin->InstantiateInterface("Window", I_ARG(const char*, "GeeXengine DirectX Window"), I_ARG(int, 0), I_ARG(int, 0), I_ARG(int, 640), I_ARG(int, 480));

    if(!window)
        throw GeexEngineException("Win32Window interface instantiation failed");

    return window;
}

TimingInformation* WindowsOpenGLApplication::CreateTimer()
{
    IPlugin* timerPlugin = pluginManager->Load("Win32Platform");
    TimingInformation* timer = (TimingInformation*)timerPlugin->InstantiateInterface("Timer");

    if(!timer)
        throw GeexEngineException("Win32Timer interface instantiation failed");

    return timer;
}

InputManager* WindowsOpenGLApplication::CreateInputDevices(Window* forWindow)
{
    IPlugin* inputPlugin = pluginManager->Load("DirectInput");
    InputManager* input = (InputManager*)inputPlugin->InstantiateInterface("Input", I_ARG(Window*, forWindow));

    if(!input)
        throw GeexEngineException("DirectInput interface instantiation failed");

    return input;
}
