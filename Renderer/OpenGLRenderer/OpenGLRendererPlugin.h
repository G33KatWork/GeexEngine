#ifndef _GX_OPENGLRENDERERPLUGIN_H_
#define _GX_OPENGLRENDERERPLUGIN_H_

#include "OpenGLRendererExports.h"
#include <Plugins/IPlugin.h>

class OpenGLRendererPlugin : public IPlugin
{
public:
    virtual const char* GetName() const;
    virtual const char* GetDescriptiveName() const;
};

extern "C" OPENGLRENDERER_API IPlugin* InstantiatePlugin();

#endif
