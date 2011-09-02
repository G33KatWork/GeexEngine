#include "DirectInputPlugin.h"

DEFINE_PLUGIN();

const char* DirectInputPlugin::GetName() const
{
    return "directinput";
}

const char* DirectInputPlugin::GetDescriptiveName() const
{
    return "Direct Input";
}

DIRECTINPUT_API IPlugin* InstantiatePlugin()
{
    return new DirectInputPlugin();
}
