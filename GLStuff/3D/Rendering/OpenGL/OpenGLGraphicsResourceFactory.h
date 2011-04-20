#ifndef _OGLGRAPHICSRESOURCEFACTORY_H_
#define _OGLGRAPHICSRESOURCEFACTORY_H_

#include <3D/Rendering/GraphicsResourceFactory.h>

#include <CG/cg.h>

class OpenGLGraphicsResourceFactory : public GraphicsResourceFactory
{
public:
    OpenGLGraphicsResourceFactory();
    virtual ~OpenGLGraphicsResourceFactory();

    virtual Effect* CreateEffectFromFile(const char* filename);
    virtual Effect* CreateEffectFromPrecompiledCode(void* code);
    virtual Effect* CreateEffectFromCode(const char* code);

    virtual IndexBuffer* CreateIndexBuffer(size_t indexCount, IndexElementType type);
    virtual VertexBuffer* CreateVertexBuffer(size_t vertexCount, VertexBufferFormat& format);

    virtual Texture* CreateTextureFromFile(const char* filename);

private:
    CGcontext cgContext;

    //prevent copying
    OpenGLGraphicsResourceFactory(const OpenGLGraphicsResourceFactory& other) {}
};

#endif
