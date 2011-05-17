#ifndef _GEEXENGINEEXCEPTION_H_
#define _GEEXENGINEEXCEPTION_H_

#include <stdexcept>

#include <Common/GeexEngineExports.h>

class GEEXENGINE_API GeexEngineException : public std::exception
{
public:
    GeexEngineException(const char* message)
        : exception(message)
    {}
};

#endif
