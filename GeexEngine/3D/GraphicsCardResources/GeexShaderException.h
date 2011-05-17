#ifndef _GEEXSHADEREXCEPTION_H_
#define _GEEXSHADEREXCEPTION_H_

#include <Common/GeexEngineException.h>
#include <Common/GeexEngineExports.h>

class GeexShaderException : public GeexEngineException
{
private:
    const char* compilerErrors;

public:
    GeexShaderException(const char* message)
        : GeexEngineException(message),
        compilerErrors(NULL)
    {}

    GeexShaderException(const char* message, const char* compilerErrors)
        : GeexEngineException(message),
        compilerErrors(compilerErrors)
    {}

    const char* GetCompilerErrors() { return compilerErrors; }
};

#endif
