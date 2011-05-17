#ifndef _WGLRENDERER_H_
#define _WGLRENDERER_H_

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "../OpenGLRenderer.h"
#include "../OpenGLRendererExports.h"

class OPENGLRENDERER_API WGLRenderer : public OpenGLRenderer
{
public:
    WGLRenderer(HWND window, int width, int height);
    virtual ~WGLRenderer();

    virtual void ToggleFullscreen();

    virtual void SwapBuffers();

protected:
    HDC deviceContext;
    HGLRC renderingContext;
    GLuint pixelFormat;

    HWND windowHandle;

    RECT oldWindowRect;
};

#endif
