#pragma once

#include <source_location>
#include <type_traits>

#include "base.hpp"
#include "log.hpp"

#ifdef TE_ASSERTS_ENABLED

#define TE_ASSERT(condition, ...) \
if(!(condition)){ \
TE_CORE_ERROR("Assert failed: {0}", fmt::format(__VA_ARGS__));\
TE_CORE_WARN("Assert Info: FILE :- {0} | LINE :- {1}", std::source_location::current().file_name(), std::source_location::current().line());\
TE_DEBUGBREAK();\
}

#else

#define TE_ASEERT(condition, ...)

#endif