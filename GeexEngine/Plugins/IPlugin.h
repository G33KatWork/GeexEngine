#ifndef _GX_IPLUGIN_H_
#define _GX_IPLUGIN_H_

#include <cstring>
#include <Plugins/Interface.h>

class IPlugin;

//TODO: Add dependencies to other plugins

//Function pointer typedef for exported dll function for plugin instantiation
typedef IPlugin* (*InstantiatePluginPtr)();


//The plugin baseclass
class IPlugin
{
public:
    virtual const char* GetName() const = 0;
    virtual const char* GetDescriptiveName() const = 0;

    virtual void* InstantiateInterface(const char* name)
    {
        InterfaceRegistration* next = InterfaceRegistration::knownInterfaces;
        while(next)
        {
            if(strcmp(next->name, name) == 0)
                return next->instantiate();

            next = next->next;
        }

        return NULL;
    }
};


//Defines a new plugin
#define DEFINE_PLUGIN() \
    InterfaceRegistration* InterfaceRegistration::knownInterfaces = NULL;

#endif
