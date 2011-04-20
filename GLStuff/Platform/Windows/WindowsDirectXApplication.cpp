#include <Platform/Windows/WindowsDirectXApplication.h>

#include <Platform/Windows/Win32Window.h>
#include <3D/Rendering/DirectX/DirectXRenderer.h>
#include <Timing/Windows/WindowsTiming.h>
#include <Input/DirectInput/DirectInputInputManager.h>

Renderer* WindowsDirectXApplication::CreateRenderer(Window* forWindow)
{
    return new DirectXRenderer(((Win32Window*)forWindow)->GetWindowHandle(), forWindow->GetWidth(), forWindow->GetHeight());
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
