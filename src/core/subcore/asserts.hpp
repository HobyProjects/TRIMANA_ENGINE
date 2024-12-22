#pragma once

#include <type_traits>

#include "base.hpp"
#include "log.hpp"

#ifdef TRIMANA_ASSERTS_ENABLED

/**
 * @brief Asserts a condition and logs an error if the condition is false.
 * @details This template function checks if the given condition is true.
 * If the condition is false, it logs an error message using the core logger
 * and triggers a debug break. The condition must be of integral type.
 *
 * @tparam T The type of the condition.
 * @tparam Args Variadic template for additional arguments to the logger.
 * @param[in] condition The condition to be checked.
 * @param[in] args Additional arguments for the error message.
 */
template<typename T, typename... Args>
void TRIMANA_ASSERT(T condition, Args&&... args){
    // Ensure the condition is of an integral type.
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