#ifndef _GEEXENGINEEXCEPTION_H_
#define _GEEXENGINEEXCEPTION_H_

#include <stdexcept>

class GeexEngineException : public std::exception
{
public:
    GeexEngineException(const char* message)
        : exception(message)
    {}
};

#endif
