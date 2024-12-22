#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "base.hpp"

namespace trimana::core{

    class TRIMANA_API logger{
        private:
            logger() = default;
            ~logger() = default;

        public:
            static std::shared_ptr<spdlog::logger>& get_core_logger();
            static std::shared_ptr<spdlog::logger>& get_client_logger();
    };
}

template<typename... Args>
inline TRIMANA_API void TRIMANA_CORE_TRACE(Args&&... args){
    trimana::core::logger::get_core_logger()->trace(str_fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline TRIMANA_API void TRIMANA_CORE_INFO(Args&&... args){
    trimana::core::logger::get_core_logger()->info(str_fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline TRIMANA_API void TRIMANA_CORE_WARN(Args&&... args){
    trimana::core::logger::get_core_logger()->warn(str_fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline TRIMANA_API void TRIMANA_CORE_ERROR(Args&&... args){
    trimana::core::logger::get_core_logger()->error(str_fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline TRIMANA_API void TRIMANA_CORE_CRITICAL(Args&&... args){
    trimana::core::logger::get_core_logger()->critical(str_fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline TRIMANA_API void TRIMANA_TRACE(Args&&... args){
    trimana::core::logger::get_client_logger()->trace(str_fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline TRIMANA_API void TRIMANA_INFO(Args&&... args){
    trimana::core::logger::get_client_logger()->info(str_fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline TRIMANA_API void TRIMANA_WARN(Args&&... args){
    trimana::core::logger::get_client_logger()->warn(str_fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline TRIMANA_API void TRIMANA_ERROR(Args&&... args){
    trimana::core::logger::get_client_logger()->error(str_fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline TRIMANA_API void TRIMANA_CRITICAL(Args&&... args){
    trimana::core::logger::get_client_logger()->critical(str_fmt, std::forward<Args>(args)...);
}
