#ifndef _GRAPHICSRESOURCEFACTORY_H_
#define _GRAPHICSRESOURCEFACTORY_H_

#include <Common/GeexEngineExports.h>

#include <3D/GraphicsCardResources/Effect.h>
#include <3D/GraphicsCardResources/IndexBuffer.h>
#include <3D/GraphicsCardResources/Texture.h>
#include <3D/GraphicsCardResources/VertexBuffer.h>
#include <3D/GraphicsCardResources/RenderSurface.h>

enum EffectType
{
    GX_EFFECT_TYPE_NATIVE,
    GX_EFFECT_TYPE_CG
};

class GEEXENGINE_API GraphicsResourceFactory
{
protected:
    GraphicsResourceFactory() {}

public:
    virtual ~GraphicsResourceFactory() {}

    virtual Effect* CreateEffectFromFile(const char* filename, EffectType type) = 0;
    virtual Effect* CreateEffectFromPrecompiledCode(void* code, EffectType type) = 0;
    virtual Effect* CreateEffectFromCode(const char* code, EffectType type) = 0;

    virtual IndexBuffer* CreateIndexBuffer(size_t indexCount, IndexElementType type) = 0;
    virtual VertexBuffer* CreateVertexBuffer(size_t vertexCount, VertexBufferFormat& format) = 0;

    virtual Texture* CreateTextureFromFile(const char* filename) = 0;

private:
    //prevent copying
    GraphicsResourceFactory(const GraphicsResourceFactory& other) {}
};

#endif
