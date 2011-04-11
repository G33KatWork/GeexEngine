#include "DirectXIndexBuffer.h"
#include <3D/Rendering/GeexRendererException.h>

DirectX9IndexBuffer::DirectX9IndexBuffer(IDirect3DDevice9 *device, size_t indexCount, IndexElementType type)
    : IndexBuffer(indexCount, type),
    device(device),
    indexBuffer(NULL)
{
    if(FAILED(device->CreateIndexBuffer(
        indexCount * sizeof(GetDXIndexType(this->elementType)),
        0,  //TODO: define usage
        GetDXIndexType(this->elementType),
        D3DPOOL_MANAGED,    //TODO: define pool
        &indexBuffer,
        NULL
    )))
        throw new GeexRendererException("Creation of index buffer failed");
}

DirectX9IndexBuffer::~DirectX9IndexBuffer()
{
    if(indexBuffer)
    {
        indexBuffer->Release();
        indexBuffer = NULL;
    }
}

void DirectX9IndexBuffer::Activate()
{
    if(FAILED(device->SetIndices(indexBuffer)))
        throw new GeexRendererException("Setting of index buffer failed");
}

void DirectX9IndexBuffer::Deactivate()
{
    if(FAILED(device->SetIndices(NULL)))
        throw new GeexRendererException("Unsetting of index buffer failed");
}

void DirectX9IndexBuffer::SetData(void* data)
{
    void *pIndexBuffer = NULL;
    if(FAILED(indexBuffer->Lock(0, indexCount * GetDXIndexTypeSize(GetDXIndexType(this->elementType)), &pIndexBuffer, 0)))
        throw new GeexRendererException("Locking of index buffer failed");

    memcpy(pIndexBuffer, data, indexCount * GetDXIndexTypeSize(GetDXIndexType(this->elementType)));

    if(FAILED(indexBuffer->Unlock()))
        throw new GeexRendererException("Unlocking of index buffer failed");
}

D3DFORMAT DirectX9IndexBuffer::GetDXIndexType(IndexElementType type)
{
    switch(type)
    {
    case GX_IB_ELEMENT_TYPE_UINT16:
        return D3DFMT_INDEX16;
    case GX_IB_ELEMENT_TYPE_UINT32:
        return D3DFMT_INDEX32;
    }

    throw new GeexRendererException("Unknown IndexElementType supplied");
}

size_t DirectX9IndexBuffer::GetDXIndexTypeSize(D3DFORMAT type)
{
    switch(type)
    {
    case D3DFMT_INDEX16:
        return sizeof(unsigned short);
    case D3DFMT_INDEX32:
        return sizeof(unsigned int);
    }

    throw new GeexRendererException("Unappropriate D3DFORMAT supplied");
}
