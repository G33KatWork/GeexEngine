#ifndef _DIRECTXRENDERER_INSTANTIATION_H_
#define _DIRECTXRENDERER_INSTANTIATION_H_

#include "DirectXRendererExports.h"
#include "DirectXRenderer.h"
#include <Platform/Window.h>

extern "C" DIRECTXRENDERER_API Renderer* InstantiateRenderer(Window* window, int width, int height);

#endif
