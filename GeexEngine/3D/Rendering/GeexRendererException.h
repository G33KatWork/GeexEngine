#ifndef _GEEXRENDEREREXCEPTION_H_
#define _GEEXRENDEREREXCEPTION_H_

#include <Common/GeexEngineException.h>

class GeexRendererException : public GeexEngineException
{
public:
    GeexRendererException(const char* message)
        : GeexEngineException(message)
    {}
};

#endif
