#include "log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace trimana::core{

    static bool s_Initialized = false;
    static std::shared_ptr<spdlog::logger> s_CoreLogger = nullptr;
    static std::shared_ptr<spdlog::logger> s_ClientLogger = nullptr;

    static void init_loggers(){
        std::vector<spdlog::sink_ptr> log_sinks{};
        log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        log_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("tromana.log", true));
        log_sinks[0]->set_pattern("%^[%T] %n: %v%$");
        log_sinks[1]->set_pattern("[%T][%l] %n: %v");

        s_CoreLogger = std::make_shared<spdlog::logger>("TRIMANA:CORE", std::begin(log_sinks), std::end(log_sinks));
        spdlog::register_logger(s_CoreLogger);
        s_CoreLogger->set_level(spdlog::level::trace);
        s_CoreLogger->flush_on(spdlog::level::trace);

        s_ClientLogger = std::make_shared<spdlog::logger>("TRIMANA:Client", std::begin(log_sinks), std::end(log_sinks)); 
        spdlog::register_logger(s_ClientLogger);
        s_ClientLogger->set_level(spdlog::level::trace);
        s_ClientLogger->flush_on(spdlog::level::trace);

        s_Initialized = true;
    }

    std::shared_ptr<spdlog::logger>& logger::get_core_logger(){
        if(!s_Initialized)
            init_loggers();

        return s_CoreLogger;
    }

    std::shared_ptr<spdlog::logger>& logger::get_client_logger(){
        if(!s_Initialized)
            init_loggers();

        return s_ClientLogger;
    }   
}