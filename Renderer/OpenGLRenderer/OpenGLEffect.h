#ifndef _OGLEFFECT_H_
#define _OGLEFFECT_H_

#include <3D/GraphicsCardResources/Effect.h>
#include "OpenGLHeader.h"
#include "OpenGLRendererExports.h"

//TODO: Multiple passes
//TODO: Defer uniform setting until program is activated
//TODO: Implement uniform getting/setting
//TODO: Enhance glsw to support programs to be used in more than one technique
//TODO: Tesselation support

class OPENGLRENDERER_API OpenGLEffect : public Effect
{
public:
    OpenGLEffect(void* code);
    OpenGLEffect(const char* sourceCode);
    OpenGLEffect(const char* filename, bool fromFile);
    virtual ~OpenGLEffect();

    void SetTechniqueByName(const char* name);

    virtual void Begin();
    virtual void End();

    //returns true if there is a next pass
    virtual bool ExecutePass();

    virtual void GetInt(const char* name, int* i);
    virtual void GetFloat(const char* name, float* f);
    virtual void GetBool(const char* name, bool* b);
    virtual void GetVector(const char* name, Vector2* v);
    virtual void GetVector(const char* name, Vector3* v);
    virtual void GetVector(const char* name, Vector4* v);
    virtual void GetMatrix(const char* name, Matrix4* m);

    virtual void SetInt(const char* name, int i);
    virtual void SetFloat(const char* name, float f);
    virtual void SetBool(const char* name, bool b);
    virtual void SetVector(const char* name, Vector2& v);
    virtual void SetVector(const char* name, Vector3& v);
    virtual void SetVector(const char* name, Vector4& v);
    virtual void SetMatrix(const char* name, Matrix4& m);

    virtual void SetTexture(const char* name, Texture* t);

private:
    void destroyCurrentTechnique();
    void compileShader(const char* source, GLuint handle);

    GLint retrieveParameter(const char* name);

    const char* effectFile;

    GLuint vertexShaderObject;
    GLuint geometryShaderObject;
    GLuint fragmentShaderObject;

    GLuint programObject;

    bool firstPass;

    //prevent copying
    OpenGLEffect(const OpenGLEffect& other) {}
};

#endif
