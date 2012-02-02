#ifndef _GX_RESOURCE_H_
#define _GX_RESOURCE_H_

#include <Common/GeexEngineExports.h>

class GEEXENGINE_API Resource
{
public:
    virtual ~Resource() {}

    virtual void Dispose() {}
};

#endif
