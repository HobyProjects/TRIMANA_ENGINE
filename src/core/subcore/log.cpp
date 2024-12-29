#include "log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace TE::Core
{
	static std::once_flag s_Initialized;
	static std::shared_ptr<spdlog::logger> s_CoreLogger = nullptr;
	static std::shared_ptr<spdlog::logger> s_EngineLogger = nullptr;

	static void init_loggers()
	{
		std::vector<spdlog::sink_ptr> log_skin{};
		log_skin.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		log_skin.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("trimana.log", true));
		log_skin [0]->set_pattern("%^[%T] %n: %v%$");
		log_skin [1]->set_pattern("[%T][%l] %n: %v");

		s_CoreLogger = std::make_shared<spdlog::logger>("Trimana::core", std::begin(log_skin), std::end(log_skin));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_EngineLogger = std::make_shared<spdlog::logger>("Trimana::app", std::begin(log_skin), std::end(log_skin));
		spdlog::register_logger(s_EngineLogger);
		s_EngineLogger->set_level(spdlog::level::trace);
		s_EngineLogger->flush_on(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger>& Logger::CoreLogger()
	{
		std::call_once(s_Initialized, init_loggers);
		return s_CoreLogger;
	}

	std::shared_ptr<spdlog::logger>& Logger::EngineLogger()
	{
		std::call_once(s_Initialized, init_loggers);
		return s_EngineLogger;
	}
}