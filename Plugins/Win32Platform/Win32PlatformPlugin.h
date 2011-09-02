#ifndef _GX_WIN32PLATFORMPLUGIN_H_
#define _GX_WIN32PLATFORMPLUGIN_H_

#include "Win32PlatformPluginExports.h"
#include <Plugins/IPlugin.h>

class Win32PlatformPlugin : public IPlugin
{
public:
    virtual const char* GetName() const;
    virtual const char* GetDescriptiveName() const;
};

extern "C" WIN32PLATFORM_API IPlugin* InstantiatePlugin();

#endif
