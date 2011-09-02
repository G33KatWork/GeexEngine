#ifndef _GX_IPLUGIN_H_
#define _GX_IPLUGIN_H_

#include <cstring>
#include <cstdarg>
#include <string>
#include <algorithm>
#include <Plugins/Interface.h>

class IPlugin;

//TODO: Add dependencies to other plugins

//Function pointer typedef for exported dll function for plugin instantiation
typedef IPlugin* (*InstantiatePluginPtr)();

//Convenience macro for instantiation parameters
#define I_ARG(type, value) InterfaceParameter<type>(#type, value)

//Generic parameter which holds a pointer to the parameter value
class GenericInterfaceParameter
{
private:
    const char* _type;
    const void* _data;

public:
    inline GenericInterfaceParameter(const char* type = NULL, const void* data = NULL)
        : _type(type),
        _data(data)
    {}

    inline const char* type() { return _type; }
    inline void* data() { return const_cast<void*>(_data); }
};

//Convenience parameter class which converts the value into a pointer
template <typename T>
class InterfaceParameter : public GenericInterfaceParameter
{
public:
    inline InterfaceParameter(const char *type, const T &data)
        : GenericInterfaceParameter(type, static_cast<const void*>(&data))
    {}
};

#include <iostream>
//The plugin baseclass
class IPlugin
{
public:
    virtual const char* GetName() const = 0;
    virtual const char* GetDescriptiveName() const = 0;

    /** Creates an instance of a named interface and passes appropriate parameters to the constructor
      * if a compatible one exists
      * Example call:     TestInterface* a = (TestInterface*)plugin->InstantiateInterface("MultiTestInterface");
      * With arguments:   TestInterface* a = (TestInterface*)plugin->InstantiateInterface("MultiTestInterface", I_ARG(const char*, "Text1"), I_ARG(int, 123));
      * If the named interface could not be found or no constructor with the given argument list
      * exists, NULL is returned
      *
      * Implementation detail: This method is defined in a header file because it needs to exist on its
      * own in each module (dll, so or dylib) you are compiling as a plugin, because it accesses the
      * static list containing all registered interfaces. If it would be exported from the engine core,
      * it would access the static module list from the core engine module, which is not what we want.
      */
    virtual void* InstantiateInterface(const char* name,
                                       GenericInterfaceParameter arg1 = GenericInterfaceParameter(),
                                       GenericInterfaceParameter arg2 = GenericInterfaceParameter(),
                                       GenericInterfaceParameter arg3 = GenericInterfaceParameter(),
                                       GenericInterfaceParameter arg4 = GenericInterfaceParameter(),
                                       GenericInterfaceParameter arg5 = GenericInterfaceParameter())
    {
        void* instantiated = NULL;

        void* args[] = { arg1.data(), arg2.data(), arg3.data(), arg4.data(), arg5.data() };

        InterfaceRegistration* next = InterfaceRegistration::knownInterfaces;
        while(next)
        {
            //Compare interface names
            if(strcmp(next->name, name) == 0)
            {
                //Build argument type strings
                std::string interfaceArgSig = std::string(next->argumentSignature);
                std::string wantedArgString = "";
                if(arg1.type()) wantedArgString += arg1.type();
                if(arg2.type()) wantedArgString += arg2.type();
                if(arg3.type()) wantedArgString += arg3.type();
                if(arg4.type()) wantedArgString += arg4.type();
                if(arg5.type()) wantedArgString += arg5.type();

                //Removing whitespaces... Yes, it's that complicated -_-
                interfaceArgSig.erase(std::remove_if(interfaceArgSig.begin(), interfaceArgSig.end(), isspace), interfaceArgSig.end());
                wantedArgString.erase(std::remove_if(wantedArgString.begin(), wantedArgString.end(), isspace), wantedArgString.end());

                //Compare argument strings
                if(interfaceArgSig.compare(wantedArgString) == 0)
                {
                    instantiated = next->instantiate(args);
                    break;
                }
            }

            next = next->next;
        }

        return instantiated;
    }
};


/* Defines a new plugin
 * Place this macro into the cpp file where your exported plugin instantiation function is implemented
 *
 * It initializes the head pointer of the linked list of registered interfaces in this module with NULL.
 */
#define DEFINE_PLUGIN() \
    InterfaceRegistration* InterfaceRegistration::knownInterfaces = NULL;

#endif
