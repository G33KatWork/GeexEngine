#include "OpenGLShader.h"
#include <fstream>
#include "Rendering/OpenGL/Utils/ExtensionManager.h"
#include "Common/DebugMessages.h"
#include "Rendering/OpenGL/Utils/OpenGLDebugMessages.h"

using namespace std;

OpenGLShaderObject::OpenGLShaderObject()
{
    if(!ExtensionManager::GLSLAvailable())
        ErrorExit("Shader support doesn't seem to be available.");

    compilerLog = 0;
    isCompiled = false;
    shaderObject = 0;
    shaderSource = 0;
    shaderSourceAllocated = false;
}


OpenGLShaderObject::~OpenGLShaderObject(void)
{
    if(compilerLog)
    {
        delete compilerLog;
        compilerLog = NULL;
    }

    if(shaderSource && shaderSourceAllocated)
    {
        delete[] shaderSource;
        shaderSource = NULL;
    }

    if(shaderObject)
    {
        glDeleteObjectARB(shaderObject);
        //CHECK_GL_ERROR();
    }
}

unsigned long getFileLength(ifstream& file)
{
    if(!file.good()) return 0;
    
    unsigned long pos = file.tellg();
    file.seekg(0, ios::end);
    unsigned long len = file.tellg();
    file.seekg(ios::beg);
    
    return len;
}

int OpenGLShaderObject::LoadFromFile(const char* filename)
{
    ifstream file;
    file.open(filename, ios::in);

    if(!file) return -1;

    unsigned long fileLen = getFileLength(file);
    if(fileLen == 0) return -2;

    //already loaded?
    if (shaderSource!=0)
    {
        if (shaderSourceAllocated)
            delete[] shaderSource;
    }

    shaderSource = (GLubyte*) new char[fileLen+1];
    if (!shaderSource) return -3;
    shaderSourceAllocated = true;
     
    shaderSource[fileLen] = 0;

    unsigned int i = 0;
    while (file.good())
    {
        shaderSource[i] = file.get();	//read characters
        if (!file.eof())
        i++;
    }
    
    shaderSource[i] = 0;
    file.close();
    return 0;
}

void OpenGLShaderObject::LoadFromMemory(const char* program)
{
    if (shaderSource!=0)    // there is already a source loaded, free it!
    {
        if (shaderSourceAllocated)
        delete[] shaderSource;
    }
   shaderSourceAllocated = false;
   shaderSource = (GLubyte*) program;
}

bool OpenGLShaderObject::Compile()
{
    GLint compiled;

    isCompiled = false;

    if(!shaderSource) return false;

    if(!shaderObject) shaderObject = GetShaderObject();

    GLint length = strlen((const char*)shaderSource);
    glShaderSourceARB(shaderObject, 1, (const GLcharARB **)&shaderSource, &length);
    CHECK_GL_ERROR();

    glCompileShaderARB(shaderObject);
    CHECK_GL_ERROR();
    glGetObjectParameterivARB(shaderObject, GL_COMPILE_STATUS, &compiled);
    CHECK_GL_ERROR();

    if(compiled) isCompiled = true;
    return isCompiled;
}

char* OpenGLShaderObject::GetCompilerLog()
{
    if(!shaderObject) return "Shader object is invalid. Forgot to compile?";

    GLint length;
    GLsizei stringLen;

    glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
    CHECK_GL_ERROR();

    if(length > 1)
    {
        if(compilerLog)
        {
            free(compilerLog);
            compilerLog = NULL;
        }

        if ((compilerLog = (GLcharARB*)malloc(length)) == NULL) 
        {
            ErrorExit("Error while allocating memory for shader compiler log. Out of Memory?");
            return "Out of memory";
        }

        glGetInfoLogARB(shaderObject, length, &stringLen, compilerLog);
        CHECK_GL_ERROR();
    }

    if(compilerLog)
        return (char*)compilerLog;
    else
        return "Compiler log not available";

    return "Unknown compiler error";
}

GLint OpenGLShaderObject::GetAttributeLocation(char* attributeName)
{
    return glGetAttribLocationARB(shaderObject, attributeName);
}
