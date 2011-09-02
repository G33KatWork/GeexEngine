#include "Win32PlatformPlugin.h"

DEFINE_PLUGIN();

const char* Win32PlatformPlugin::GetName() const
{
    return "win32platform";
}

const char* Win32PlatformPlugin::GetDescriptiveName() const
{
    return "Win32 Platform Layer";
}

WIN32PLATFORM_API IPlugin* InstantiatePlugin()
{
    return new Win32PlatformPlugin();
}
