#include <3D/Rendering/Renderer.h>
#include <3D/Rendering/GeexRendererException.h>

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

size_t Renderer::GetVertexCount(PrimitiveType type, size_t primitiveCount)
{
    switch(type)
    {
    case PRIMTYPE_POINTLIST: 
        return primitiveCount; 

    case PRIMTYPE_LINELIST: 
        return primitiveCount * 2; 
    case PRIMTYPE_LINESTRIP: 
        return primitiveCount + 1; 

    case PRIMTYPE_TRIANGLELIST: 
        return primitiveCount * 3; 

    case PRIMTYPE_TRIANGLESTRIP: 
    case PRIMTYPE_TRIANGLEFAN: 
        return primitiveCount + 2; 
    }

    throw new GeexEngineException("Invalid PrimitiveType passed");
}
