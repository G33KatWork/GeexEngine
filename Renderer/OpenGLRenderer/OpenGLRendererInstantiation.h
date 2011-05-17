#ifndef _OPENGLRENDERER_INSTANTIATION_H_
#define _OPENGLRENDERER_INSTANTIATION_H_

#include "OpenGLRendererExports.h"
#include "OpenGLRenderer.h"
#include <Platform/Window.h>

extern "C" OPENGLRENDERER_API Renderer* InstantiateRenderer(Window* window, int width, int height);

#endif
