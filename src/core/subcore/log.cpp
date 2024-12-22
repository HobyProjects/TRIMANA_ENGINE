#include "log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace trimana::core {

	/// A flag to indicate if the loggers have been initialized.
	static std::once_flag s_Initialized;

	/// The logger for the core of the application.
	///
	/// This logger is initialized with a stdout_color_sink_mt
	/// and a basic_file_sink_mt writing to "tromana.log".
	/// Both sinks are configured to print the log level and
	/// the logger name.
	static std::shared_ptr<spdlog::logger> s_CoreLogger = nullptr;

	/// The logger for the client of the application.
	///
	/// This logger is initialized with a stdout_color_sink_mt
	/// and a basic_file_sink_mt writing to "tromana_client.log".
	/// Both sinks are configured to print the log level and
	/// the logger name.
	static std::shared_ptr<spdlog::logger> s_ClientLogger = nullptr;

	/// Initializes the loggers for the core and the client.
	///
	/// This function is called once when the get_core_logger() or
	/// get_client_logger() functions are called for the first time.
	///
	/// The core logger is named "TRIMANA:CORE" and the client logger
	/// is named "TRIMANA:Client". Both loggers have two sinks: a
	/// stdout_color_sink_mt and a basic_file_sink_mt. The stdout
	/// sink prints the log level, the logger name and the log message
	/// to the console. The file sink prints the log level, the logger
	/// name, the timestamp and the log message to the file specified
	/// in the constructor. The file sink is configured to rotate the
	/// log file every day at 2am.
	static void init_loggers() {
		std::vector<spdlog::sink_ptr> log_sinks{};
		log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>("tromana.log", 2, 0));
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
	}

	std::shared_ptr<spdlog::logger>& logger::get_core_logger() {
		std::call_once(s_Initialized, init_loggers);
		return s_CoreLogger;
	}

	std::shared_ptr<spdlog::logger>& logger::get_client_logger() {
		std::call_once(s_Initialized, init_loggers);
		return s_ClientLogger;
	}
}