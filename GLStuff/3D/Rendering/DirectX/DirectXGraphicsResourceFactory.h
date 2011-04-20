#ifndef _DX9GRAPHICSRESOURCEFACTORY_H_
#define _DX9GRAPHICSRESOURCEFACTORY_H_

#include <3D/Rendering/GraphicsResourceFactory.h>
#include <3D/Rendering/DirectX/DirectXResettableResource.h>

#include <CG/cg.h>
#include <d3d9.h>

class DirectXGraphicsResourceFactory : public GraphicsResourceFactory, DirectXResettableResource
{
public:
    DirectXGraphicsResourceFactory(IDirect3DDevice9* device);
    virtual ~DirectXGraphicsResourceFactory();

    virtual Effect* CreateEffectFromFile(const char* filename);
    virtual Effect* CreateEffectFromPrecompiledCode(void* code);
    virtual Effect* CreateEffectFromCode(const char* code);

    virtual IndexBuffer* CreateIndexBuffer(size_t indexCount, IndexElementType type);
    virtual VertexBuffer* CreateVertexBuffer(size_t vertexCount, VertexBufferFormat& format);

    virtual Texture* CreateTextureFromFile(const char* filename);

    //DirectXResettableResource members
    virtual void OnDeviceLost();
    virtual void OnDeviceReset();

private:
    //prevent copying
    DirectXGraphicsResourceFactory(const DirectXGraphicsResourceFactory& other) {}

    CGcontext cgContext;
    IDirect3DDevice9* d3d9Device;
};

#endif
