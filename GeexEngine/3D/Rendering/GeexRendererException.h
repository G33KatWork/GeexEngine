#ifndef _GEEXRENDEREREXCEPTION_H_
#define _GEEXRENDEREREXCEPTION_H_

#include <Common/GeexEngineExports.h>
#include <Common/GeexEngineException.h>

class GEEXENGINE_API GeexRendererException : public GeexEngineException
{
public:
    GeexRendererException(const char* message)
        : GeexEngineException(message)
    {}
};

#endif
