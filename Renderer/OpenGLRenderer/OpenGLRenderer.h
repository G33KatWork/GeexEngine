#ifndef _OPENGLRENDERER_H_
#define _OPENGLRENDERER_H_

#include <3D/Rendering/Renderer.h>
#include "OpenGLHeader.h"
#include "OpenGLRendererExports.h"

typedef struct
{
    float m[16];
} OGLMATRIX;

class OPENGLRENDERER_API OpenGLRenderer : public Renderer
{
public:
    virtual ~OpenGLRenderer();

    virtual GraphicsResourceFactory* GetGraphicsResourceFactory() { return resourceFactory; }

    virtual void Resize(int newWidth, int newHeight);
    virtual void ToggleFullscreen() = 0;

    virtual bool BeginScene();
    virtual void EndScene();

    virtual void ClearBackBuffer();
    virtual void ClearDepthBuffer();
    virtual void ClearStencilBuffer();
    virtual void ClearBuffers();

    virtual void DrawPrimitive(PrimitiveType primitiveType, unsigned int startVertex, size_t primitiveCount);
    virtual void DrawIndexedPrimitive(IndexElementType indexElementType, PrimitiveType primitiveType, unsigned int startIndex, unsigned int vertexCountInBuffer, size_t primitiveCount);
    
    virtual void SwapBuffers() = 0;

    virtual void SetBackgroundColor(Color newColor);

    virtual void UpdateCamera(ICamera* camera);

    //TODO: remove me...
    static OGLMATRIX ToOGLMatrix(Matrix4 m);

protected:
    OpenGLRenderer(int width, int height);

    GraphicsResourceFactory* resourceFactory;
};

#endif
