#ifndef _GX_DIRECTXRENDERERPLUGIN_H_
#define _GX_DIRECTXRENDERERPLUGIN_H_

#include "DirectXRendererExports.h"
#include <Plugins/IPlugin.h>

class DirectXRendererPlugin : public IPlugin
{
public:
    virtual const char* GetName() const;
    virtual const char* GetDescriptiveName() const;
};

extern "C" DIRECTXRENDERER_API IPlugin* InstantiatePlugin();

#endif
