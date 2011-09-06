#ifndef _GX_PLUGINMANAGER_H_
#define _GX_PLUGINMANAGER_H_

#include <Common/GeexEngineExports.h>
#include <Plugins/IPlugin.h>
#include <set>

#pragma warning( push )
//disable dll interface warning for std::list stuff
#pragma warning( disable : 4251 )

//TODO: add dependencies to other plugins

class GEEXENGINE_API PluginManager
{
private:
    std::set<IPlugin*> loadedPlugins;
    

public:
    IPlugin* Load(const char* name);

    IPlugin* GetPlugin(const char* name);
};

#pragma warning( pop )

#endif
