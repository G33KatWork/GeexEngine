#include <Resources/ResourceManager.h>

#include <Resources/GeexEngineResourceException.h>
#include <Utils/Path.h>

#include <iostream>
using namespace std;

ResourceManager::ResourceManager()
    : archiveList()
{
}

ResourceManager::~ResourceManager()
{
    //TODO: dispose resources
}

void ResourceManager::AddArchive(const char* path)
{
    if(!Path(path).Exists())
        throw GeexEngineResourceException("Given resource directory doesn't exist");

    //TODO: Implement resource container files
    if(Path(path).IsFile())
        throw GeexEngineResourceException("Only resource directories are supported for now");

    archiveList.push_front(path);
}

Resource* ResourceManager::Load(const char* assetName)
{
    Path foundPath("");
    for(std::list<const char*>::const_iterator it = archiveList.begin(); it != archiveList.end(); it++)
    {
        if((Path(*it)+assetName).IsFile())
            foundPath = Path(*it)+assetName;
    }

    if(foundPath == Path(""))
        throw GeexEngineResourceException("Resource file not found");

    cout << foundPath.GetExtension();
    
    return NULL;
}

void ResourceManager::Unload(Resource* resource)
{
    if(!resource)
        return;

    resource->Dispose();
    delete resource;
}
