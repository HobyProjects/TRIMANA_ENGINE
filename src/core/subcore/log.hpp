#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "base.hpp"

namespace trimana::core{
    class logger{
        private:
            logger() = default;
            ~logger() = default;
        public:
            static std::shared_ptr<spdlog::logger>& get_core_logger();
            static std::shared_ptr<spdlog::logger>& get_client_logger();
    };
}

template<typename... Args> void TRIMANA_CORE_TRACE(Args&&... args){ trimana::core::logger::get_core_logger()->trace(std::forward<Args>(args)...); }
template<typename... Args> void TRIMANA_CORE_INFO(Args&&... args){ trimana::core::logger::get_core_logger()->info(std::forward<Args>(args)...); }
template<typename... Args> void TRIMANA_CORE_WARN(Args&&... args){ trimana::core::logger::get_core_logger()->warn(std::forward<Args>(args)...); }
template<typename... Args> void TRIMANA_CORE_ERROR(Args&&... args){ trimana::core::logger::get_core_logger()->error(std::forward<Args>(args)...); }
template<typename... Args> void TRIMANA_CORE_CRITICAL(Args&&... args){ trimana::core::logger::get_core_logger()->critical(std::forward<Args>(args)...); }

template<typename... Args> void TRIMANA_TRACE(Args&&... args){ trimana::core::logger::get_client_logger()->trace(std::forward<Args>(args)...); }
template<typename... Args> void TRIMANA_INFO(Args&&... args){ trimana::core::logger::get_client_logger()->info(std::forward<Args>(args)...); }
template<typename... Args> void TRIMANA_WARN(Args&&... args){ trimana::core::logger::get_client_logger()->warn(std::forward<Args>(args)...); }
template<typename... Args> void TRIMANA_ERROR(Args&&... args){ trimana::core::logger::get_client_logger()->error(std::forward<Args>(args)...); }
template<typename... Args> void TRIMANA_CRITICAL(Args&&... args){ trimana::core::logger::get_client_logger()->critical(std::forward<Args>(args)...); }
