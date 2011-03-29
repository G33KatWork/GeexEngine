#ifndef _OPENGL_SHADER_H_
#define _OPENGL_SHADER_H_

#include "Rendering/OpenGL/OpenGLHeader.h"

class OpenGLShaderObject
{
	friend class OpenGLEffect;

public:
	virtual ~OpenGLShaderObject(void);

	int LoadFromFile(const char* filename);
	void LoadFromMemory(const char* program);

	bool Compile();
	char* GetCompilerLog();
	GLint GetAttributeLocation(char* attributeName);
	bool IsCompiled() { return isCompiled; }

	enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };

protected:
	OpenGLShaderObject();

	virtual GLuint GetShaderObject() = 0;
	virtual ShaderType GetShaderType() = 0;

private:
	GLuint shaderObject;
	GLcharARB* compilerLog;
	GLubyte* shaderSource;
	bool isCompiled;
	bool shaderSourceAllocated;
};

//-------------------------------------------------------------------------------------------------

class OpenGLVertexShaderObject : public OpenGLShaderObject
{
public:
	OpenGLVertexShaderObject() : OpenGLShaderObject() {}
	virtual ~OpenGLVertexShaderObject() {}

protected:
	virtual GLuint GetShaderObject() { return glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB); }
	virtual ShaderType GetShaderType() { return OpenGLShaderObject::VERTEX_SHADER; }
};

//-------------------------------------------------------------------------------------------------

class OpenGLFragmentShaderObject : public OpenGLShaderObject
{
public:
	OpenGLFragmentShaderObject() : OpenGLShaderObject() {}
	virtual ~OpenGLFragmentShaderObject() {}

protected:
	virtual GLuint GetShaderObject() { return glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB); }
	virtual ShaderType GetShaderType() { return OpenGLShaderObject::FRAGMENT_SHADER; }
};

//-------------------------------------------------------------------------------------------------

class OpenGLGeometryShaderObject : public OpenGLShaderObject
{
public:
	OpenGLGeometryShaderObject() : OpenGLShaderObject() {}
	virtual ~OpenGLGeometryShaderObject() {}

protected:
	virtual GLuint GetShaderObject() { return glCreateShaderObjectARB(GL_GEOMETRY_SHADER_EXT); }
	virtual ShaderType GetShaderType() { return OpenGLShaderObject::GEOMETRY_SHADER; }
};

#endif