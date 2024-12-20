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
#endif