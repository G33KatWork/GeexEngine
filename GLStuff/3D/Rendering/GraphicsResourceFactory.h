#ifndef _GRAPHICSRESOURCEFACTORY_H_
#define _GRAPHICSRESOURCEFACTORY_H_

#include <3D/GraphicsCardResources/Effect.h>
#include <3D/GraphicsCardResources/IndexBuffer.h>
#include <3D/GraphicsCardResources/Texture.h>
#include <3D/GraphicsCardResources/VertexBuffer.h>

class GraphicsResourceFactory
{
protected:
    GraphicsResourceFactory() {}

public:
    virtual ~GraphicsResourceFactory() {}

    virtual Effect* CreateEffectFromFile(const char* filename) = 0;
    virtual Effect* CreateEffectFromPrecompiledCode(void* code) = 0;
    virtual Effect* CreateEffectFromCode(const char* code) = 0;

    virtual IndexBuffer* CreateIndexBuffer(size_t indexCount, IndexElementType type) = 0;
    virtual VertexBuffer* CreateVertexBuffer(size_t vertexCount, VertexBufferFormat& format) = 0;

    virtual Texture* CreateTextureFromFile(const char* filename) = 0;

private:
    //prevent copying
    GraphicsResourceFactory(const GraphicsResourceFactory& other) {}
};

#endif
