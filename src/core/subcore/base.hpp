#pragma once

#include <type_traits>

#ifdef TE_DEBUG

    #if defined(TE_PLATFORM_WINDOWS)
    #define TE_DEBUGBREAK() __debugbreak()

#elif defined(TE_PLATFORM_LINUX)

    #include <signal.h>
    #define TE_DEBUGBREAK() raise(SIGTRAP)
    
#else
    #error "Platform doesn't support debugbreak yet!"
#endif

    #define TE_INSTRUMENTS_ENABLED
    #define TE_ASSERTS_ENABLED

#else

    #define TE_DEBUGBREAK()

#endif

#define TE_BIT(x) (1 << x)
#define TE_MACTOSTRING(x) #x