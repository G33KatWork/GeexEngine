#ifndef _OPENGLRENDERER_H_
#define _OPENGLRENDERER_H_

#include <3D/Rendering/Renderer.h>
#include <3D/Rendering/OpenGL/OpenGLHeader.h>

typedef struct
{
    float m[16];
} OGLMATRIX;

class OpenGLRenderer : public Renderer
{
public:
    virtual ~OpenGLRenderer() {}

    virtual void Resize(int newWidth, int newHeight);
    virtual void ToggleFullscreen() = 0;

    virtual bool BeginScene();
    virtual void EndScene();

    virtual void ClearBackBuffer();
    virtual void ClearDepthBuffer();
    virtual void ClearStencilBuffer();
    virtual void ClearBuffers();

    virtual void DrawPrimitive(unsigned int startVertex, size_t primitiveCount, PrimitiveType primitiveType);
    virtual void DrawIndexedPrimitive(int baseVertexIndex, unsigned int minIndex, unsigned int startIndex, size_t primitiveCount, PrimitiveType primitiveType);

    virtual void SwapBuffers() = 0;

    virtual void SetBackgroundColor(Color newColor);

    virtual void UpdateCamera(ICamera* camera);

    //TODO: remove me...
    static OGLMATRIX ToOGLMatrix(Matrix4 m);

protected:
    OpenGLRenderer(int width, int height);

private:
    GLenum GetGLPrimitiveType(PrimitiveType type);
};

#endif
