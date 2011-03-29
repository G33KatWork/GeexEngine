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

    virtual void SwapBuffers() = 0;

    virtual void SetWorldMatrix(Matrix4 m);
    virtual void SetViewMatrix(Matrix4 m);
    virtual void SetProjectionMatrix(Matrix4 m);

	virtual void SetBackgroundColor(Color newColor);

	virtual void UpdateCamera(ICamera* camera);

protected:
    OpenGLRenderer(int width, int height);

private:
	OGLMATRIX ToOGLMatrix(Matrix4 m);
};

#endif
