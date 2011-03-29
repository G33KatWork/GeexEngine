#include <3D/GraphicsCardResources/VertexBuffer.h>
#include <Math/Color.h>
#include <cassert>

size_t VertexElement::GetTypeSize(VertexElementType type)
{
    switch(type)
    {
    case GX_VB_ELEMENT_TYPE_COLOR:
    case GX_VB_ELEMENT_TYPE_COLOR_ABGR:
    case GX_VB_ELEMENT_TYPE_COLOR_ARGB:
        return sizeof(Color);
    case GX_VB_ELEMENT_TYPE_FLOAT1:
        return sizeof(float);
    case GX_VB_ELEMENT_TYPE_FLOAT2:
        return sizeof(float) * 2;
    case GX_VB_ELEMENT_TYPE_FLOAT3:
        return sizeof(float) * 3;
    case GX_VB_ELEMENT_TYPE_FLOAT4:
        return sizeof(float) * 4;
    case GX_VB_ELEMENT_TYPE_SHORT2:
        return sizeof(short) * 2;
    case GX_VB_ELEMENT_TYPE_SHORT4:
        return sizeof(short) * 4;
    case GX_VB_ELEMENT_TYPE_UBYTE4:
        return sizeof(unsigned char) * 4;
    }

    return 0;
}

VertexBuffer::VertexBuffer(size_t vertexCount, VertexBufferFormat& format)
    : vertexCount(vertexCount), 
    format(format)
{
}


VertexBuffer::~VertexBuffer(void)
{
}

const VertexElement* VertexBufferFormat::GetElements(unsigned short at)
{
    assert(at < elements.size() && "Index out of bounds");

    VertexElementList::const_iterator i = elements.begin();
    for (unsigned short n = 0; n < at; n++)
        i++;

    return &(*i);
}

void VertexBufferFormat::AddElement(size_t offset, size_t size, VertexElementUsage usage, VertexElementType type)
{
    elements.push_back(VertexElement(type, usage, offset, size));
}

void VertexBufferFormat::AddElement(unsigned short at, size_t offset, size_t size, VertexElementUsage usage, VertexElementType type)
{
    if (at >= elements.size())
        return AddElement(offset, size, usage, type);

    VertexElementList::iterator i = elements.begin();
    for (unsigned short n = 0; n < at; n++)
        i++;

    elements.insert(i, VertexElement(type, usage, offset, size));
}

void VertexBufferFormat::RemoveElement(unsigned short at)
{
    VertexElementList::iterator i = elements.begin();

    for (unsigned short n = 0; n < at; n++)
        i++;

    elements.remove(*i);
}

size_t VertexBufferFormat::GetTotalVertexSize() const
{
    size_t total = 0;

    VertexElementList::const_iterator i = elements.begin();
    for (unsigned short n = 0; n < elements.size(); n++)
    {
        total += i->size;
        i++;
    }

    return total;
}
