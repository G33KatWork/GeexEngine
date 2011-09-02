#include "DirectXRendererPlugin.h"

DEFINE_PLUGIN();

const char* DirectXRendererPlugin::GetName() const
{
    return "dx9renderer";
}

const char* DirectXRendererPlugin::GetDescriptiveName() const
{
    return "DirectX 9 Rendering Backend";
}

DIRECTXRENDERER_API IPlugin* InstantiatePlugin()
{
    return new DirectXRendererPlugin();
}
