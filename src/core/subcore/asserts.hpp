#pragma once

#include <type_traits>

#include "base.hpp"
#include "log.hpp"

#ifdef TRIMANA_ASSERTS_ENABLED

template<typename T, typename... Args>
inline TRIMANA_API void TRIMANA_ASSERT(T condition, Args&&... args){
    if(!condition){
        TRIMANA_CORE_ERROR("Assertion failed: {0}", std::forward<Args>(args)...);
        TRIMANA_DEBUGBREAK();
    }
}

#else

template<typename T, typename... Args>
inline TRIMANA_API void TRIMANA_ASSERT(T condition, Args&&... args){
    // Do nothing
}

#endif