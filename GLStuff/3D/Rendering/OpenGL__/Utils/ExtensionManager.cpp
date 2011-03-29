#include "3D/Rendering/OpenGL/Utils/ExtensionManager.h"
#include "3D/Rendering/OpenGL/Utils/OpenGLDebugMessages.h"
#include "Common/DebugMessages.h"
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>

bool ExtensionManager::InitExtensions()
{
	GLenum err = glewInit();

	if(err != GLEW_OK)
	{
		DebugMsg("GLEW Error: %s\n", (char*)glewGetErrorString(err));
		return false;
	}

	DebugMsg("Initialized GLEW\n");
	DebugMsg("OpenGL Vendor: %s\n", (char*)glGetString(GL_VENDOR));
	DebugMsg("OpenGL Renderer: %s\n", (char*)glGetString(GL_RENDERER));
	DebugMsg("OpenGL Version: %s\n", (char*)glGetString(GL_VERSION));
	DebugMsg("OpenGL Extensions: %s\n", (char*)glGetString(GL_EXTENSIONS));

	return true;
}

bool ExtensionManager::IsExtensionAvailable(const char* ext)
{
	return glewGetExtension(ext) == GL_TRUE;
}

bool ExtensionManager::IsOpenGLVersion2()
{
	return GLEW_VERSION_2_0 == GL_TRUE;
}

bool ExtensionManager::GLSLAvailable()
{
	bool avail = true;

	if(!IsExtensionAvailable("GL_ARB_fragment_shader"))
	{
		CHECK_GL_ERROR();
		avail = false;
		DebugMsg("WARNING: Exension GL_ARB_fragment_shader is not available");
	}

	if(!IsExtensionAvailable("GL_ARB_vertex_shader"))
	{
		CHECK_GL_ERROR();
		avail = false;
		DebugMsg("WARNING: Exension GL_ARB_vertex_shader is not available");
	}

	if(!IsExtensionAvailable("GL_ARB_shader_objects"))
	{
		CHECK_GL_ERROR();
		avail = false;
		DebugMsg("WARNING: Exension GL_ARB_shader_objects is not available");
	}

	return avail;
}

bool ExtensionManager::GeometryShaderSupportAvailable()
{
	return glewGetExtension("GL_EXT_geometry_shader4") == GL_TRUE;
}

bool ExtensionManager::ShaderModel4Available()
{
	return glewGetExtension("GL_EXT_gpu_shader4") == GL_TRUE;
}
