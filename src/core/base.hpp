#pragma once

#ifdef TRIMANA_DEBUG
#if defined(TRIMANA_PLATFORM_WINDOWS)
    #define TRIMANA_DEBUGBREAK() __debugbreak()
#elif defined(TRIMANA_PLATFORM_LINUX)
    #include <signal.h>
    #define TRIMANA_DEBUGBREAK() raise(SIGTRAP)
#else   
    #error "Platform doesn't support debugbreak yet!"
#endif
#ifdef TRIMANA_BUILD_SHARED
    #if defined(TRIMANA_PLATFORM_WINDOWS)
        #ifdef TRIMANA_EXPORT
            #define TRIMANA_API __declspec(dllexport)
        #else
            #define TRIMANA_API __declspec(dllimport)
        #endif
    #elif defined(TRIMANA_PLATFORM_LINUX)
        #define TRIMANA_API __attribute__((visibility("default")))
    #else
        #define TRIMANA_API
    #endif
#endif // TRIMANA_WINDOW_BUILD_SHARED
#ifdef TRIMANA_BUILD_STATIC
    #define TRIMANA_API
#endif // TRIMANA_WINDOW_BUILD_STATIC
#endif // TRIMANA_DEBUG

#ifdef TRIMANA_RELEASE
    #define TRIMANA_DEBUGBREAK()
#endif // TRIMANA_RELEASE

#define TRIMANA_TOSTRING(x) #x
#define TRIMANA_BIT(x) (1 << x)