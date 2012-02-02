#ifndef _GX_IRESOURCELOADER_H_
#define _GX_IRESOURCELOADER_H_

#include <Resources/Resource.h>
#include <Utils/Path.h>

class IResourceLoader
{
public:
    virtual Resource* Load(Path& assetName) = 0;
    virtual void Unload(Resource* resource) = 0;
};

#endif
