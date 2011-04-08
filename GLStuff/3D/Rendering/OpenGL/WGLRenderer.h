#ifndef _WGLRENDERER_H_
#define _WGLRENDERER_H_

#include <3D/Rendering/OpenGL/OpenGLRenderer.h>
#include <Windows.h>

class WGLRenderer : public OpenGLRenderer
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
