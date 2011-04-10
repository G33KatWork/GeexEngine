#include <3D/GraphicsCardResources/VertexBuffer.h>
#include <Math/Color.h>
#include <cassert>

size_t VertexElement::GetTypeSize(VertexElementType type)
{
    switch(type)
    {
    case GX_VB_ELEMENT_TYPE_FLOAT:
        return sizeof(float);
    case GX_VB_ELEMENT_TYPE_SHORT:
        return sizeof(short);
    case GX_VB_ELEMENT_TYPE_UBYTE:
        return sizeof(unsigned char);
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

void VertexBufferFormat::AddElement(size_t offset, size_t componentCount, VertexElementUsage usage, VertexElementType type)
{
    elements.push_back(VertexElement(type, usage, offset, componentCount));
}

void VertexBufferFormat::AddElement(unsigned short at, size_t offset, size_t componentCount, VertexElementUsage usage, VertexElementType type)
{
    if (at >= elements.size())
        return AddElement(offset, componentCount, usage, type);

    VertexElementList::iterator i = elements.begin();
    for (unsigned short n = 0; n < at; n++)
        i++;

    elements.insert(i, VertexElement(type, usage, offset, componentCount));
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
        total += VertexElement::GetTypeSize(i->type) * i->componentCount;
        i++;
    }

    return total;
}
