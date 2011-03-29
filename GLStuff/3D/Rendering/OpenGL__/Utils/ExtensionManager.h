#ifndef _EXTENSIONMANAGER_H_
#define _EXTENSIONMANAGER_H_

class ExtensionManager
{
public:
	static bool InitExtensions(void);
	static bool IsExtensionAvailable(const char* ext);
	static bool IsOpenGLVersion2(void);
	static bool GLSLAvailable(void);
	static bool GeometryShaderSupportAvailable(void);
	static bool ShaderModel4Available(void);
};

#endif
