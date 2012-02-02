#ifndef _GEEXENGINERESOURCEEXCEPTION_H_
#define _GEEXENGINERESOURCEEXCEPTION_H_

#include <Common/GeexEngineException.h>

class GEEXENGINE_API GeexEngineResourceException : public GeexEngineException
{
public:
    GeexEngineResourceException(const char* message)
        : GeexEngineException(message)
    {}
};

#endif
