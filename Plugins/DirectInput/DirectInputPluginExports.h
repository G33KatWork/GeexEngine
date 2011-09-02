#ifndef _DIRECTINPUTPLUGIN_EXPORTS_H_
#define _DIRECTINPUTPLUGIN_EXPORTS_H_

#if defined(_WIN32) || defined(_WIN64)
    #ifdef DIRECTINPUTPLUGIN_EXPORTS
    #define DIRECTINPUT_API __declspec(dllexport)
    #else
    #define DIRECTINPUT_API __declspec(dllimport)
    #endif
#else
    #define DIRECTINPUT_API
#endif

#endif
