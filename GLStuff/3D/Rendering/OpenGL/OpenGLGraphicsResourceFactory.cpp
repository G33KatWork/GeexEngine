#include "OpenGLGraphicsResourceFactory.h"

#include <3D/Rendering/Cg/CgEffect.h>
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
//#include "OpenGLTexture.h"

#include <CG/cgGL.h>

OpenGLGraphicsResourceFactory::OpenGLGraphicsResourceFactory()
    : cgContext(NULL)
{
    cgContext = cgCreateContext();
    cgGLRegisterStates(cgContext);
}

OpenGLGraphicsResourceFactory::~OpenGLGraphicsResourceFactory()
{
    cgDestroyContext(cgContext);
}

Effect* OpenGLGraphicsResourceFactory::CreateEffectFromFile(const char* filename)
{
    return new CgEffect(cgContext, filename, true);
}

Effect* OpenGLGraphicsResourceFactory::CreateEffectFromPrecompiledCode(void* code)
{
    return new CgEffect(cgContext, code);
}

Effect* OpenGLGraphicsResourceFactory::CreateEffectFromCode(const char* code)
{
    return new CgEffect(cgContext, code);
}

IndexBuffer* OpenGLGraphicsResourceFactory::CreateIndexBuffer(size_t indexCount, IndexElementType type)
{
    return new OpenGLIndexBuffer(indexCount, type);
}

VertexBuffer* OpenGLGraphicsResourceFactory::CreateVertexBuffer(size_t vertexCount, VertexBufferFormat& format)
{
    return new OpenGLVertexBuffer(vertexCount, format);
}

Texture* OpenGLGraphicsResourceFactory::CreateTextureFromFile(const char* filename)
{
    return NULL;
}
