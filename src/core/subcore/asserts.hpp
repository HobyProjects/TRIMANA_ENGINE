#pragma once

#include <type_traits>
#include "base.hpp"
#include "log.hpp"

#ifdef TE_ASSERTS_ENABLED

template<typename T, typename... Args>
void TE_ASSERT(T condition, Args&&... args)
{
	// Ensure the condition is of an integral type.
	static_assert( std::is_integral<T>::value, "Condition must be of integral type" );
	if( !condition )
	{
		TE_CORE_ERROR("Assertion failed: {0}", std::forward<Args>(args)...);
		TE_DEBUGBREAK();
	}
}

#else

template<typename T, typename... Args>
inline void TRIMANA_ASSERT(T condition, Args&&... args)
{
	// Do nothing
}

#endif