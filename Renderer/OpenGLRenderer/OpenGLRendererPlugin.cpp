#include "OpenGLRendererPlugin.h"

DEFINE_PLUGIN();

const char* OpenGLRendererPlugin::GetName() const
{
    return "openglrenderer";
}

const char* OpenGLRendererPlugin::GetDescriptiveName() const
{
    return "OpenGL Rendering Backend";
}

OPENGLRENDERER_API IPlugin* InstantiatePlugin()
{
    return new OpenGLRendererPlugin();
}
