#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

#include <3D/GraphicsCardResources/IGraphicsCardResource.h>
#include <Common/GeexEngineExports.h>

#include <list>

enum VertexElementUsage
{
    GX_VB_ELEMENT_USAGE_POSITION,
    GX_VB_ELEMENT_USAGE_NORMAL,
    GX_VB_ELEMENT_USAGE_TEXTURE_COORDINATES,
    GX_VB_ELEMENT_USAGE_COLOR,
    /*GX_VB_ELEMENT_USAGE_DIFFUSE,
    GX_VB_ELEMENT_USAGE_SPECULAR,*/
};

enum VertexElementType
{
    GX_VB_ELEMENT_TYPE_FLOAT,
    GX_VB_ELEMENT_TYPE_SHORT,
    GX_VB_ELEMENT_TYPE_UBYTE,
};

class GEEXENGINE_API VertexElement
{
public:
    VertexElementType type;
    VertexElementUsage usage;
    size_t offset;
    size_t componentCount;

    VertexElement() {}
    VertexElement(VertexElementType type, VertexElementUsage usage, size_t offset, size_t componentCount)
        : type(type), usage(usage), offset(offset), componentCount(componentCount)
    {}

    inline bool operator==(const VertexElement& other)
    {
        return
            other.offset == offset &&
            other.componentCount == componentCount &&
            other.type == type &&
            other.usage == usage;
    }

    static size_t GetTypeSize(VertexElementType type);
};

class GEEXENGINE_API VertexBufferFormat
{
public:
    typedef std::list<VertexElement> VertexElementList;

protected:
    VertexElementList elements;

public:
    size_t GetElementCount() const { return elements.size(); }

    const VertexBufferFormat::VertexElementList& GetElements() { return elements; }
    const VertexElement* GetElements(unsigned short at);

    void AddElement(size_t offset, size_t componentCount, VertexElementUsage usage, VertexElementType type);
    void AddElement(unsigned short at, size_t offset, size_t componentCount, VertexElementUsage usage, VertexElementType type);
    void RemoveElement(unsigned short at);
    void RemoveAllElements() { elements.clear(); }

    size_t GetTotalVertexSize() const;
};

class GEEXENGINE_API VertexBuffer /*:
    public IGraphicsCardResource*/
{
protected:
    size_t vertexCount;
    VertexBufferFormat format;

    VertexBuffer(size_t vertexCount, VertexBufferFormat& format);

public:
    virtual ~VertexBuffer();

    size_t GetVertexCount() { return vertexCount; }

    /** Memory management **/
    /*virtual void Bind(Renderer* renderer) {}
    virtual void Unbind(Renderer* renderer) {}*/

    virtual void Activate() {}
    virtual void Deactivate() {}
    virtual void SetData(void* data) = 0;

    virtual VertexBufferFormat* GetVertexFormat() { return &format; }
};

//TODO: Vertex streams

#endif

