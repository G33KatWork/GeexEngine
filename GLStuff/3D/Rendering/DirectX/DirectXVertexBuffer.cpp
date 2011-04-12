#include "DirectXVertexBuffer.h"
#include <3D/Rendering/GeexRendererException.h>
#include <3D/Rendering/DirectX/DirectXTypeConversions.h>

DirectX9VertexBuffer::DirectX9VertexBuffer(IDirect3DDevice9 *device, size_t vertexCount, VertexBufferFormat& format)
    : VertexBuffer(vertexCount, format),
    device(device),
    vertexDeclaration(NULL),
    vertexBuffer(NULL)
{
    this->BuildDirect3DVertexDeclaration9();

    if(FAILED(device->CreateVertexBuffer(
        vertexCount * format.GetTotalVertexSize(),
        0,  //TODO: define usage
        0,  //no FVF
        D3DPOOL_MANAGED,    //TODO: define pool
        &vertexBuffer,
        NULL
    )))
        throw new GeexRendererException("Creation of vertex buffer failed");
}

DirectX9VertexBuffer::~DirectX9VertexBuffer()
{
    if(vertexBuffer)
    {
        vertexBuffer->Release();
        vertexBuffer = NULL;
    }

    if(vertexDeclaration)
    {
        vertexDeclaration->Release();
        vertexDeclaration = NULL;
    }
}

void DirectX9VertexBuffer::Activate()
{
    if(FAILED(device->SetVertexDeclaration(vertexDeclaration)))
        throw new GeexRendererException("Setting of vertex declaration failed");

    if(FAILED(device->SetStreamSource(0, vertexBuffer, 0, format.GetTotalVertexSize())))
        throw new GeexRendererException("Setting of vertex stream source failed");
}

void DirectX9VertexBuffer::Deactivate()
{
    if(FAILED(device->SetVertexDeclaration(NULL)))
        throw new GeexRendererException("Unsetting of vertex declaration failed");

    if(FAILED(device->SetStreamSource(0, NULL, 0, 0)))
        throw new GeexRendererException("Unsetting of vertex stream source failed");
}

void DirectX9VertexBuffer::SetData(void* data)
{
    void *pVertexBuffer = NULL;
    if(FAILED(vertexBuffer->Lock(0, vertexCount * format.GetTotalVertexSize(), &pVertexBuffer, 0)))
        throw new GeexRendererException("Locking of vertex buffer failed");

    memcpy(pVertexBuffer, data, vertexCount * format.GetTotalVertexSize());

    if(FAILED(vertexBuffer->Unlock()))
        throw new GeexRendererException("Unlocking of vertex buffer failed");
}

void DirectX9VertexBuffer::BuildDirect3DVertexDeclaration9()
{
    size_t vertexElementCount = format.GetElementCount();

    LPD3DVERTEXELEMENT9 declaration = new D3DVERTEXELEMENT9[vertexElementCount + 1];
    if(!declaration)
        throw new GeexRendererException("Allocation of vertex declaration array failed");

    for(size_t i = 0; i < vertexElementCount; i++)
    {
        const VertexElement* curElement = format.GetElements(i);

        declaration[i].Stream = 0;
        declaration[i].Offset = curElement->offset;
        declaration[i].Type = GetDXDeclType(curElement->type, curElement->componentCount);
        declaration[i].Method = D3DDECLMETHOD_DEFAULT;  //TODO: let user specify this crap
        declaration[i].Usage = GetDXDeclUsage(curElement->usage);
        declaration[i].UsageIndex = 0;
    }

    //Last entry for termination, see D3DDECL_END()
    declaration[vertexElementCount].Stream = 0xFF;
    declaration[vertexElementCount].Offset = 0;
    declaration[vertexElementCount].Type = D3DDECLTYPE_UNUSED;
    declaration[vertexElementCount].Method = 0;
    declaration[vertexElementCount].Usage = 0;
    declaration[vertexElementCount].UsageIndex = 0;

    HRESULT hr = device->CreateVertexDeclaration(declaration, &vertexDeclaration);
    if(FAILED(hr))
        throw new GeexRendererException("Creation of vertex declaration failed");


    delete[] declaration;
}
