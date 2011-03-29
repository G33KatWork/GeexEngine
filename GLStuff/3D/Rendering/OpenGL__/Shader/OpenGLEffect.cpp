#include "OpenGLEffect.h"
#include "Rendering/OpenGL/Utils/ExtensionManager.h"
#include "Common/DebugMessages.h"
#include "Rendering/OpenGL/Utils/OpenGLDebugMessages.h"
#include "Rendering/OpenGL/Shader/OpenGLShader.h"

OpenGLEffect::OpenGLEffect()
{
	programObject = 0;
	linkerLog = NULL;
	isLinked = false;

	if(!ExtensionManager::GLSLAvailable())
		ErrorExit("Shader support doesn't seem to be available.");

	programObject = glCreateProgram();
	shaderList = std::vector<OpenGLShaderObject*>();
}

OpenGLEffect::~OpenGLEffect()
{
	if(linkerLog) free(linkerLog);

	for(unsigned int i = 0; i < shaderList.size(); i++)
	{
		glDetachShader(programObject, shaderList[i]->shaderObject);
		CHECK_GL_ERROR();

		//TODO: Delete shader object?
	}

	if(programObject)
	{
		glDeleteShader(programObject);
		CHECK_GL_ERROR();
	}
}

void OpenGLEffect::AddShader(OpenGLShaderObject* shader)
{
	if(!shader) return;

	if(!shader->IsCompiled())
	{
		if(!shader->Compile())
		{
			DebugMsg("Compilation of shader failed. Log: %s", shader->GetCompilerLog());
			return;
		}
	}

	shaderList.push_back(shader);
}

bool OpenGLEffect::Link()
{
	return false;
}

const char* OpenGLEffect::GetLinkerLog()
{
	GLint length;
	GLsizei stringLen;

	glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &length);
	CHECK_GL_ERROR();

	if(length > 1)
	{
		if(linkerLog)
		{
			free(linkerLog);
			linkerLog = NULL;
		}

		if ((linkerLog = (GLcharARB*)malloc(length)) == NULL) 
		{
			ErrorExit("Error while allocating memory for shader linker log. Out of Memory?");
			return "Out of memory";
		}

		glGetProgramInfoLog(programObject, length, &stringLen, linkerLog);
		CHECK_GL_ERROR();
	}

	if(linkerLog)
		return (char*)linkerLog;
	else
		return "Linker log not available";

	return "Unknown linker error";
}

void OpenGLEffect::Begin()
{
	if(!programObject) return;
	if(isLinked)
	{
		glUseProgram(programObject);
		CHECK_GL_ERROR();
	}
}

void OpenGLEffect::End()
{
	glUseProgram(0);
	CHECK_GL_ERROR();
}
