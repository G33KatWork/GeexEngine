#ifndef _GEEXENGINEPLUGINEXCEPTION_H_
#define _GEEXENGINEPLUGINEXCEPTION_H_

#include <Common/GeexEngineException.h>

class GEEXENGINE_API GeexEnginePluginException : public GeexEngineException
{
public:
    GeexEnginePluginException(const char* message)
        : GeexEngineException(message)
    {}
};

#endif
