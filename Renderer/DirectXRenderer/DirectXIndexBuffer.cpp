#include "DirectXIndexBuffer.h"
#include "DirectXTypeConversions.h"

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
        throw GeexRendererException("Creation of index buffer failed");
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
        throw GeexRendererException("Setting of index buffer failed");
}

void DirectX9IndexBuffer::Deactivate()
{
    if(FAILED(device->SetIndices(NULL)))
        throw GeexRendererException("Unsetting of index buffer failed");
}

void DirectX9IndexBuffer::SetData(void* data)
{
    void *pIndexBuffer = NULL;
    if(FAILED(indexBuffer->Lock(0, indexCount * GetDXIndexTypeSize(GetDXIndexType(this->elementType)), &pIndexBuffer, 0)))
        throw GeexRendererException("Locking of index buffer failed");

    memcpy(pIndexBuffer, data, indexCount * GetDXIndexTypeSize(GetDXIndexType(this->elementType)));

    if(FAILED(indexBuffer->Unlock()))
        throw GeexRendererException("Unlocking of index buffer failed");
}
