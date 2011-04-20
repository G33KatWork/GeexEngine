#include "DirectXGraphicsResourceFactory.h"

//#include "DirectXEffect.h"
#include <3D/Rendering/Cg/CgEffect.h>
#include "DirectXIndexBuffer.h"
#include "DirectXVertexBuffer.h"
#include "DirectXTexture.h"

#include <cg/cgD3D9.h>

DirectXGraphicsResourceFactory::DirectXGraphicsResourceFactory(IDirect3DDevice9* device)
    : cgContext(NULL),
    d3d9Device(device),
    DirectXResettableResource()
{
    cgContext = cgCreateContext();
    cgD3D9RegisterStates(cgContext);
    cgD3D9SetDevice(device);
}

DirectXGraphicsResourceFactory::~DirectXGraphicsResourceFactory()
{
    cgDestroyContext(cgContext);
    cgD3D9SetDevice(NULL);
}

Effect* DirectXGraphicsResourceFactory::CreateEffectFromFile(const char* filename)
{
    return new CgEffect(cgContext, filename, true);
}

Effect* DirectXGraphicsResourceFactory::CreateEffectFromPrecompiledCode(void* code)
{
    return new CgEffect(cgContext, code);
}

Effect* DirectXGraphicsResourceFactory::CreateEffectFromCode(const char* code)
{
    return new CgEffect(cgContext, code);
}

IndexBuffer* DirectXGraphicsResourceFactory::CreateIndexBuffer(size_t indexCount, IndexElementType type)
{
    return new DirectX9IndexBuffer(d3d9Device, indexCount, type);
}

VertexBuffer* DirectXGraphicsResourceFactory::CreateVertexBuffer(size_t vertexCount, VertexBufferFormat& format)
{
    return new DirectX9VertexBuffer(d3d9Device, vertexCount, format);
}

Texture* DirectXGraphicsResourceFactory::CreateTextureFromFile(const char* filename)
{
    return new DirectXTexture(d3d9Device, filename);
}

void DirectXGraphicsResourceFactory::OnDeviceLost()
{
    cgD3D9SetDevice(NULL);
}

void DirectXGraphicsResourceFactory::OnDeviceReset()
{
    cgD3D9SetDevice(d3d9Device);
}
