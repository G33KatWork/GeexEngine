#ifndef _OGLRENDERER_EXPORTS_H_
#define _OGLRENDERER_EXPORTS_H_

#ifdef _MSC_VER
    #ifdef OPENGLRENDERER_EXPORTS
    #define OPENGLRENDERER_API __declspec(dllexport)
    #else
    #define OPENGLRENDERER_API __declspec(dllimport)
    #endif
#else
    #define OPENGLRENDERER_API
#endif

#endif
