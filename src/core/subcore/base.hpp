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
        #ifdef TRIMANA_PLATFORM_WINDOWS
            #ifdef TRIMANA_SHARED
                #define TRIMANA_API __declspec(dllexport)
            #else
                #define TRIMANA_API __declspec(dllimport)
            #endif
        #elif defined(TRIMANA_PLATFORM_LINUX)
            #ifdef TRIMANA_SHARED
                #define TRIMANA_API __attribute__((visibility("default")))
            #else
                #define TRIMANA_API
            #endif
        #endif
    #else
        #define TRIMANA_API
    #endif

    #ifdef TRIMANA_BUILD_STATIC
        #define TRIMANA_API
    #endif

    #define TRIMANA_INSTRUMENTS_ENABLED
    #define TRIMANA_ASSERTS_ENABLED

#else

    #define TRIMANA_DEBUGBREAK()

#endif

#define TRIMANA_BIT(x) (1 << x)
#define TRIMANA_MACTOSTRING(x) #x