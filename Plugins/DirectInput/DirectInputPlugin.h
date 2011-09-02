#ifndef _GX_DIRECTINPUTPLUGIN_H_
#define _GX_DIRECTINPUTPLUGIN_H_

#include "DirectInputPluginExports.h"
#include <Plugins/IPlugin.h>

class DirectInputPlugin : public IPlugin
{
public:
    virtual const char* GetName() const;
    virtual const char* GetDescriptiveName() const;
};

extern "C" DIRECTINPUT_API IPlugin* InstantiatePlugin();

#endif
