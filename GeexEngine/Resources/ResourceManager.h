#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <Common/GeexEngineExports.h>
#include <Resources/Resource.h>

#include <list>

#pragma warning( push )
//disable dll interface warning for std::list stuff
#pragma warning( disable : 4251 )

class GEEXENGINE_API ResourceManager
{
private:
    std::list<const char*> archiveList;

public:
    ResourceManager();
    ~ResourceManager();

    void AddArchive(const char* path);

    Resource* Load(const char* assetName);
    void Unload(Resource* resource);
};

#pragma warning( pop )

#endif
