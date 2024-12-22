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

#define TRIMANA_CORE_TRACE(...) ::trimana::core::logger::get_core_logger()->trace(__VA_ARGS__)
#define TRIMANA_CORE_INFO(...) ::trimana::core::logger::get_core_logger()->info(__VA_ARGS__)
#define TRIMANA_CORE_WARN(...) ::trimana::core::logger::get_core_logger()->warn(__VA_ARGS__)    
#define TRIMANA_CORE_ERROR(...) ::trimana::core::logger::get_core_logger()->error(__VA_ARGS__)
#define TRIMANA_CORE_CRITICAL(...) ::trimana::core::logger::get_core_logger()->critical(__VA_ARGS__)

#define TRIMANA_TRACE(...) ::trimana::core::logger::get_client_logger()->trace(__VA_ARGS__)
#define TRIMANA_INFO(...) ::trimana::core::logger::get_client_logger()->info(__VA_ARGS__)
#define TRIMANA_WARN(...) ::trimana::core::logger::get_client_logger()->warn(__VA_ARGS__)    
#define TRIMANA_ERROR(...) ::trimana::core::logger::get_client_logger()->error(__VA_ARGS__)
#define TRIMANA_CRITICAL(...) ::trimana::core::logger::get_client_logger()->critical(__VA_ARGS__)