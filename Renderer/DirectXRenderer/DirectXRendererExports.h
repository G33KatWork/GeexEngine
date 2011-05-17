#ifndef _DIRECTXRENDERER_EXPORTS_H_
#define _DIRECTXRENDERER_EXPORTS_H_

#ifdef _MSC_VER
    #ifdef DIRECTXRENDERER_EXPORTS
    #define DIRECTXRENDERER_API __declspec(dllexport)
    #else
    #define DIRECTXRENDERER_API __declspec(dllimport)
    #endif
#else
    #define DIRECTXRENDERER_API
#endif

#endif
