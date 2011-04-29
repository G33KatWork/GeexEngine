#include "OpenGLEffect.h"
#include <3D/GraphicsCardResources/GeexShaderException.h>

#include <string>

OpenGLEffect::OpenGLEffect(void* code)
    : vertexShaderObject(NULL),
    geometryShaderObject(NULL),
    fragmentShaderObject(NULL),
    programObject(NULL)
{
    throw new GeexEngineException("Not yet implemented");
}

OpenGLEffect::OpenGLEffect(const char* sourceCode)
    : vertexShaderObject(NULL),
    geometryShaderObject(NULL),
    fragmentShaderObject(NULL),
    programObject(NULL)
{
    throw new GeexEngineException("Not yet implemented");
}

OpenGLEffect::OpenGLEffect(const char* filename, bool fromFile)
    : vertexShaderObject(NULL),
    geometryShaderObject(NULL),
    fragmentShaderObject(NULL),
    programObject(NULL)
{
    effectFile = filename;
}

OpenGLEffect::~OpenGLEffect()
{
    destroyCurrentTechnique();
}

void OpenGLEffect::destroyCurrentTechnique()
{
    glDeleteProgram(programObject);
    programObject = NULL;

    glDeleteShader(vertexShaderObject);
    vertexShaderObject = NULL;
    glDeleteShader(geometryShaderObject);
    geometryShaderObject = NULL;
    glDeleteShader(fragmentShaderObject);
    fragmentShaderObject = NULL;
}

void OpenGLEffect::compileShader(const char* source, GLuint handle)
{
    glShaderSource(handle, 1, &source, 0);
    glCompileShader(handle);

    GLint compileSuccess;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compileSuccess);

    if(!compileSuccess)
    {
        GLchar compilerSpew[4096];
        glGetShaderInfoLog(handle, sizeof(compilerSpew), 0, compilerSpew);

        throw new GeexShaderException("Compilation of GLSL shader failed", compilerSpew);
    }
}

void OpenGLEffect::SetTechniqueByName(const char* name)
{
    destroyCurrentTechnique();

    std::string genericName(effectFile);
    genericName = genericName + "." + name + ".";

    //get source
    const char* vsSource = glswGetShader((genericName + "VS").c_str());
    const char* gsSource = glswGetShader((genericName + "GS").c_str());
    const char* fsSource = glswGetShader((genericName + "FS").c_str());
    
    //compile shader
    if(!vsSource)
        throw new GeexShaderException("No vertex shader in given technique found");
    else
    {
        vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
        compileShader(vsSource, vertexShaderObject);
    }

    if(gsSource)
    {
        geometryShaderObject = glCreateShader(GL_GEOMETRY_SHADER);
        compileShader(gsSource, geometryShaderObject);
    }

    if(fsSource)
    {
        fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
        compileShader(fsSource, fragmentShaderObject);
    }

    //attach shaders
    programObject = glCreateProgram();
    glAttachShader(programObject, vertexShaderObject);

    if(geometryShaderObject)
        glAttachShader(programObject, geometryShaderObject);

    if(fragmentShaderObject)
        glAttachShader(programObject, fragmentShaderObject);

    //link finished program
    glLinkProgram(programObject);

    GLint linkSuccess;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linkSuccess);
    if(!linkSuccess)
    {
        GLchar linkerSpew[4096];
        glGetProgramInfoLog(programObject, sizeof(linkerSpew), 0, linkerSpew);

        throw new GeexShaderException("Linking of GLSL program failed", linkerSpew);
    }
}

void OpenGLEffect::Begin()
{
    if(!programObject)
        throw new GeexShaderException("No valid technique was selected");

    glUseProgram(programObject);
    if(glGetError())
        throw new GeexShaderException("Activation of GLSL program failed");

    firstPass = true;
}

void OpenGLEffect::End()
{
    glUseProgram(0);
}

bool OpenGLEffect::ExecutePass()
{
    if(firstPass)
    {
        firstPass = false;
        return true;
    }

    return false;
}

void OpenGLEffect::GetInt(const char* name, int* i)
{
    glGetUniformiv(this->programObject, retrieveParameter(name), i);
}

void OpenGLEffect::GetFloat(const char* name, float* f)
{
    glGetUniformfv(this->programObject, retrieveParameter(name), f);
}

void OpenGLEffect::GetBool(const char* name, bool* b)
{
    int i;
    glGetUniformiv(this->programObject, retrieveParameter(name), &i);

    if(i == 0)
        *b = false;
    else
        *b = true;
}

void OpenGLEffect::GetVector(const char* name, Vector2* v)
{
    float f[2];
    glGetUniformfv(this->programObject, retrieveParameter(name), f);

    *v = Vector2(f[0], f[1]);
}

void OpenGLEffect::GetVector(const char* name, Vector3* v)
{
    float f[3];
    glGetUniformfv(this->programObject, retrieveParameter(name), f);

    *v = Vector3(f[0], f[1], f[2]);
}

void OpenGLEffect::GetVector(const char* name, Vector4* v)
{
    float f[4];
    glGetUniformfv(this->programObject, retrieveParameter(name), f);

    *v = Vector4(f[0], f[1], f[2], f[3]);
}

void OpenGLEffect::GetMatrix(const char* name, Matrix4* m)
{
    float f[16];
    glGetUniformfv(this->programObject, retrieveParameter(name), f);

    *m = Matrix4(f);
}

void OpenGLEffect::SetInt(const char* name, int i)
{
    glUniform1i(retrieveParameter(name), i);
}

void OpenGLEffect::SetFloat(const char* name, float f)
{
    glUniform1f(retrieveParameter(name), f);
}

void OpenGLEffect::SetBool(const char* name, bool b)
{
    glUniform1i(retrieveParameter(name), b ? 1 : 0);
}

void OpenGLEffect::SetVector(const char* name, Vector2& v)
{
    glUniform2f(retrieveParameter(name), v.GetX(), v.GetY());
}

void OpenGLEffect::SetVector(const char* name, Vector3& v)
{
    glUniform3f(retrieveParameter(name), v.GetX(), v.GetY(), v.GetZ());
}

void OpenGLEffect::SetVector(const char* name, Vector4& v)
{
    glUniform4f(retrieveParameter(name), v.GetX(), v.GetY(), v.GetZ(), v.GetW());
}

void OpenGLEffect::SetMatrix(const char* name, Matrix4& m)
{
    glUniformMatrix4fv(retrieveParameter(name), 1, GL_FALSE, m[0]);
}

void OpenGLEffect::SetTexture(const char* name, Texture* t)
{

}

GLint OpenGLEffect::retrieveParameter(const char* name)
{
    GLint location = glGetUniformLocation(programObject, name);
    if(location == -1)
        throw new GeexShaderException("Uniform doesn't exist");

    return location;
}
