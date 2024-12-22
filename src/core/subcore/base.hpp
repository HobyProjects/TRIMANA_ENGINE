#pragma once

#include <type_traits>

#ifdef TRIMANA_DEBUG
    #if defined(TRIMANA_PLATFORM_WINDOWS)
        #define TRIMANA_DEBUGBREAK() __debugbreak()
    #elif defined(TRIMANA_PLATFORM_LINUX)
        #include <signal.h>
        #define TRIMANA_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif

    #define TRIMANA_INSTRUMENTS_ENABLED
    #define TRIMANA_ASSERTS_ENABLED

#else

    #define TRIMANA_DEBUGBREAK()

#endif

#define TRIMANA_BIT(x) (1 << x)
#define TRIMANA_MACTOSTRING(x) #x