#include "OpenGLRenderer.h"
#include "OpenGLTypeConversions.h"
#include "OpenGLGraphicsResourceFactory.h"

#include <3D/Rendering/GeexRendererException.h>

OpenGLRenderer::OpenGLRenderer(int width, int height)
    : Renderer(width, height),
    resourceFactory(NULL)
{
    resourceFactory = new OpenGLGraphicsResourceFactory();
}

OpenGLRenderer::~OpenGLRenderer()
{
    if(resourceFactory)
    {
        delete resourceFactory;
        resourceFactory = NULL;
    }
}

void OpenGLRenderer::Resize(int newWidth, int newHeight)
{
    Renderer::Resize(newWidth, newHeight);
    glViewport(0, 0, newWidth, newHeight);

    //FIXME: Recalculate world view projection stuff
}

bool OpenGLRenderer::BeginScene()
{
    //Normally we would use glBegin() here, but since we ONLY use vertex buffers, we don't do it here
    return true;
}

void OpenGLRenderer::EndScene()
{
}

void OpenGLRenderer::ClearBackBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::ClearDepthBuffer()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::ClearStencilBuffer()
{
    glClear(GL_STENCIL_BUFFER_BIT);
}

void OpenGLRenderer::ClearBuffers()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGLRenderer::DrawPrimitive(PrimitiveType primitiveType, unsigned int startVertex, size_t primitiveCount)
{
    glDrawArrays(GetGLPrimitiveType(primitiveType), startVertex, GetVertexCount(primitiveType, primitiveCount));

    GLenum error = glGetError();
    if(error)
        throw GeexRendererException("Array drawing failed");
}

void OpenGLRenderer::DrawIndexedPrimitive(IndexElementType indexElementType, PrimitiveType primitiveType, unsigned int startIndex, unsigned int vertexCountInBuffer, size_t primitiveCount)
{
    glDrawElements(
        GetGLPrimitiveType(primitiveType),
        GetVertexCount(primitiveType, primitiveCount),
        GetGLIndexType(indexElementType),
        (void*)(startIndex * GetGLIndexTypeSize(GetGLIndexType(indexElementType)))
    );
}

void OpenGLRenderer::SetBackgroundColor(Color newColor)
{
    Renderer::SetBackgroundColor(newColor);
    glClearColor(newColor.R(), newColor.G(), newColor.B(), newColor.A());
}

void OpenGLRenderer::UpdateCamera(ICamera* camera)
{
    throw GeexRendererException("Not implemented");
}

OGLMATRIX OpenGLRenderer::ToOGLMatrix(Matrix4 m)
{
    OGLMATRIX d;

    d.m[0] = m[0][0];
    d.m[1] = m[1][0];
    d.m[2] = m[2][0];
    d.m[3] = m[3][0];

    d.m[4] = m[0][1];
    d.m[5] = m[1][1];
    d.m[6] = m[2][1];
    d.m[7] = m[3][1];

    d.m[8] = m[0][2];
    d.m[9] = m[1][2];
    d.m[10] = m[2][2];
    d.m[11] = m[3][2];
    
    d.m[12] = m[0][3];
    d.m[13] = m[1][3];
    d.m[14] = m[2][3];
    d.m[15] = m[3][3];

    return d;
}

