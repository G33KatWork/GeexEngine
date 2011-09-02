#ifndef _WIN32PLATFORMPLUGIN_EXPORTS_H_
#define _WIN32PLATFORMPLUGIN_EXPORTS_H_

#if defined(_WIN32) || defined(_WIN64)
    #ifdef WIN32PLATFORMPLUGIN_EXPORTS
    #define WIN32PLATFORM_API __declspec(dllexport)
    #else
    #define WIN32PLATFORM_API __declspec(dllimport)
    #endif
#else
    #define WIN32PLATFORM_API
#endif

#endif
