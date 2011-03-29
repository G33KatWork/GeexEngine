#ifndef _OPENGLDEBUGMESSAGES_H_
#define _OPENGLDEBUGMESSAGES_H_

#define CHECK_GL_ERROR() CheckGLError(__FILE__, __LINE__)
int CheckGLError(char *file, int line);

#endif
