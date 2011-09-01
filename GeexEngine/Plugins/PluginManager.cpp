#include <Plugins/PluginManager.h>
#include <Plugins/GeexEnginePluginException.h>

//FIXME: Move library loading into platform agnostic subclass

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
    static const char* libExtension = ".dll";
#elif defined(__linux__) 
    static const char* libExtension = ".so";
#else
#error Unsupported platform
#endif

IPlugin* PluginManager::Load(const char* filename)
{
    if(!filename)
        return NULL;

    IPlugin* loadedPlugin = NULL;

    std::string f = filename;
    f.append(libExtension);

#if defined(_WIN32) || defined(_WIN64)
    HMODULE lib = LoadLibrary(f.c_str());
    if(!lib)
        throw GeexEnginePluginException("Plugin library couldn't be loaded");

    InstantiatePluginPtr createInstance = (InstantiatePluginPtr)GetProcAddress(lib, "InstantiatePlugin");

    if(!createInstance)
        throw GeexEnginePluginException("InstantiatePlugin entry point wasn't found in plugin");

    loadedPlugin = createInstance();
#else
#error Unsupported platform
#endif

    loadedPlugins.insert(loadedPlugin);

    return loadedPlugin;
}

IPlugin* PluginManager::GetPlugin(const char* name)
{
    for(std::set<IPlugin*>::const_iterator it = loadedPlugins.begin(); it != loadedPlugins.end(); it++)
        if(strcmp(name, (*it)->GetName()) == 0)
            return *it;

    return NULL;
}
