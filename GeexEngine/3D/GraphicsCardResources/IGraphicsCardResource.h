#ifndef _IGRAPHICSCARDRESOURCE_H_
#define _IGRAPHICSCARDRESOURCE_H_

#include <Common/GeexEngineExports.h>

class Renderer;

class GEEXENGINE_API IGraphicsCardResource
{
protected:
    IGraphicsCardResource() {}

public:
    virtual void Bind(Renderer* renderer) = 0;
    virtual void Unbind(Renderer* renderer) = 0;
};

#endif
