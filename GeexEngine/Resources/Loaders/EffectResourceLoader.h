#ifndef _GX_EFFECTRESOURCELOADER_H_
#define _GX_EFFECTRESOURCELOADER_H_

#include <Common/GeexEngineExports.h>
#include <Resources/IResourceLoader.h>
#include <3D/GraphicsCardResources/Effect.h>

class GEEXENGINE_API EffectResourceLoader : public IResourceLoader
{
public:
    virtual Resource* Load(Path& assetName);
    virtual void Unload(Resource* resource);
};

#endif
