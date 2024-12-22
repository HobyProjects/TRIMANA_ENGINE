#pragma once

#include <type_traits>

#include "base.hpp"
#include "log.hpp"

#ifdef TRIMANA_ASSERTS_ENABLED

template<typename T, typename... Args>
void TRIMANA_ASSERT(T condition, Args&&... args){
    static_assert(std::is_integral<T>::value, "Condition must be of integral type");
    if(!condition){
        TRIMANA_CORE_ERROR("Assertion failed: {0}", std::forward<Args>(args)...);
        TRIMANA_DEBUGBREAK();
    }
}

#else

template<typename T, typename... Args>
inline void TRIMANA_ASSERT(T condition, Args&&... args){
    // Do nothing
}

#endif