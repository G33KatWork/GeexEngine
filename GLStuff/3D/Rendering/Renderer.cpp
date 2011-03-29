#include <3D/Rendering/Renderer.h>

Renderer::Renderer()
{
    curWidth = curHeight = 0;
    isFullscreen = false;
    backgroundColor = Color(0,0,0,1);
}

Renderer::Renderer(int width, int height)
{
    curWidth = width;
    curHeight = height;
    isFullscreen = false;
    backgroundColor = Color(0,0,0,1);
}

void Renderer::Resize(int newWidth, int newHeight)
{
    if(newWidth >= 0)
        curWidth = newWidth;

    if(newHeight >= 0)
        curHeight = newHeight;
}

void Renderer::ToggleFullscreen()
{
    isFullscreen = !isFullscreen;
}
