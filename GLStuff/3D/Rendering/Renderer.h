#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <Math/Matrix4.h>
#include <Math/Color.h>
#include <3D/Camera/ICamera.h>
#include <3D/GraphicsCardResources/Effect.h>
#include <3D/GraphicsCardResources/VertexBuffer.h>
#include <3D/GraphicsCardResources/IndexBuffer.h>
#include <3D/Rendering/GraphicsResourceFactory.h>

enum PrimitiveType
{
    PRIMTYPE_POINTLIST,
    PRIMTYPE_LINELIST,
    PRIMTYPE_LINESTRIP,
    PRIMTYPE_TRIANGLELIST,
    PRIMTYPE_TRIANGLESTRIP,
    PRIMTYPE_TRIANGLEFAN
};

class Renderer
{
protected:
    Renderer();
    Renderer(int width, int height);
    
    size_t GetVertexCount(PrimitiveType type, size_t primitiveCount);

    int curWidth, curHeight;
    bool isFullscreen;
    Color backgroundColor;

public:
    virtual ~Renderer() {}

    virtual GraphicsResourceFactory* GetGraphicsResourceFactory() = 0;

    virtual void Resize(int newWidth, int newHeight);
    virtual void ToggleFullscreen();

    virtual bool BeginScene() = 0;
    virtual void EndScene() = 0;

    virtual void ClearBackBuffer() = 0;
    virtual void ClearDepthBuffer() = 0;
    virtual void ClearStencilBuffer() = 0;
    virtual void ClearBuffers() = 0;

    virtual void DrawPrimitive(PrimitiveType primitiveType, unsigned int startVertex, size_t primitiveCount) = 0;
    virtual void DrawIndexedPrimitive(IndexElementType indexElementType, PrimitiveType primitiveType, unsigned int startIndex, size_t primitiveCount) = 0;
    
    virtual void SwapBuffers() = 0;

    virtual void UpdateCamera(ICamera* camera) = 0;

    virtual Color GetBackgroundColor() { return backgroundColor; }
    virtual void SetBackgroundColor(Color newColor) { backgroundColor = newColor; }

    virtual int GetWidth() const { return this->curWidth; }
    virtual int GetHeight() const { return this->curHeight; }
};

#endif
