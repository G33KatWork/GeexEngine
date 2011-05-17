#include "OpenGLRendererInstantiation.h"
#include "WGL/WGLRenderer.h"

#include <Platform/Windows/Win32Window.h>
#include <GL3/gl3w.h>

OPENGLRENDERER_API Renderer* InstantiateRenderer(Window* window, int width, int height)
{
    Renderer* renderer = new WGLRenderer(((Win32Window*)window)->GetWindowHandle(), width, height);

    if(FAILED(gl3wInit()))
    {
        delete renderer;
        return NULL;
        //throw new GeexEngineException("GL3W initialization failed");
    }

    return renderer;
}
