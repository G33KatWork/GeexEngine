#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Common/DebugMessages.h"

int CheckGLError(char *file, int line)
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR) 
    {
        const GLubyte* sError = gluErrorString(glErr);

        DebugMsg("GL Error #%i (%s) in File %s at line: %i\n", glErr, sError ? (const char*)sError : "no message available", file, line);
            
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}
