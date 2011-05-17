#ifndef _GEEXENGINE_EXPORTS_H_
#define _GEEXENGINE_EXPORTS_H_

#ifdef _MSC_VER
    #ifdef GEEXENGINE_EXPORTS
    #define GEEXENGINE_API __declspec(dllexport)
    #else
    #define GEEXENGINE_API __declspec(dllimport)
    #endif
#else
    #define GEEXENGINE_API
#endif

#endif
