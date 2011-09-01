#ifndef _GX_PLUGINMANAGER_H_
#define _GX_PLUGINMANAGER_H_

#include <Common/GeexEngineExports.h>
#include <Plugins/IPlugin.h>
#include <set>

//TODO: add dependencies to other plugins

class GEEXENGINE_API PluginManager
{
private:
    std::set<IPlugin*> loadedPlugins;
    

public:
    IPlugin* Load(const char* filename);

    IPlugin* GetPlugin(const char* name);
};

#endif
