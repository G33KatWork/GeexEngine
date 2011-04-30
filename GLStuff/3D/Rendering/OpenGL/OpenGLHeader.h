#ifndef _OPENGLHEADER_H_
#define _OPENGLHEADER_H_

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <gl/glew.h>
#ifdef _WIN32
#include <gl/wglew.h>
#endif

#include <gl/GL.h>
#include <gl/GLU.h>

#include <glsw.h>

#endif
