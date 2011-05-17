#include "DirectXRendererInstantiation.h"

#include <Platform/Windows/Win32Window.h>
#include <Common/GeexEngineException.h>

DIRECTXRENDERER_API Renderer* InstantiateRenderer(Window* window, int width, int height)
{
    Renderer* renderer = new DirectXRenderer(((Win32Window*)window)->GetWindowHandle(), width, height);
    return renderer;
}
