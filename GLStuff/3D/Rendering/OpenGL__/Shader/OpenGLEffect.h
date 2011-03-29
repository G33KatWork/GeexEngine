#ifndef _OPENGL_EFFECT_H_
#define _OPENGL_EFFECT_H_

#include "Rendering/OpenGL/OpenGLHeader.h"
#include <vector>

class OpenGLShaderObject;

class OpenGLEffect
{
public:
	OpenGLEffect();
	virtual ~OpenGLEffect();

	void AddShader(OpenGLShaderObject* shader);
	GLuint GetProgramObject() { return programObject; }

	bool Link();
	const char* GetLinkerLog();

	void Begin();
	void End();

private:
	GLuint programObject;
	GLcharARB* linkerLog;
	bool isLinked;
	std::vector<OpenGLShaderObject*> shaderList;
};

#endif
