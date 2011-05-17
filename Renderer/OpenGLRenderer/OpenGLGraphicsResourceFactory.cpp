#include "OpenGLGraphicsResourceFactory.h"

//#include <3D/Rendering/Cg/CgEffect.h>
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLEffect.h"
//#include "OpenGLTexture.h"

//#include <CG/cgGL.h>

OpenGLGraphicsResourceFactory::OpenGLGraphicsResourceFactory()
    /*: cgContext(NULL)*/
{
    /*cgContext = cgCreateContext();
    cgGLRegisterStates(cgContext);*/

    glswInit();
    glswSetPath("", ".glsl");
}

OpenGLGraphicsResourceFactory::~OpenGLGraphicsResourceFactory()
{
    //cgDestroyContext(cgContext);
}

Effect* OpenGLGraphicsResourceFactory::CreateEffectFromFile(const char* filename, EffectType type)
{
    if(type == GX_EFFECT_TYPE_CG)
        return NULL;
        //return new CgEffect(cgContext, filename, true);
    else
        return new OpenGLEffect(filename, true);
}

Effect* OpenGLGraphicsResourceFactory::CreateEffectFromPrecompiledCode(void* code, EffectType type)
{
    if(type == GX_EFFECT_TYPE_CG)
        return NULL;
        //return new CgEffect(cgContext, code);
    else
        return new OpenGLEffect(code);
}

Effect* OpenGLGraphicsResourceFactory::CreateEffectFromCode(const char* code, EffectType type)
{
    if(type == GX_EFFECT_TYPE_CG)
        return NULL;
        //return new CgEffect(cgContext, code);
    else
        return new OpenGLEffect(code);
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
