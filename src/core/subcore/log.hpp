#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "base.hpp"

namespace trimana::core
{
	/**
	 * @brief A class for managing the logging system.
	 * This class initializes and manages the spdlog loggers for the core and client.
	 * The loggers are thread-safe and can be accessed from any thread.
	 */
	class logger
	{
	private:
		/**
		 * @brief Private constructor to prevent instantiation.
		 */
		logger() = default;
		/**
		 * @brief Private destructor to prevent instantiation.
		 */
		~logger() = default;

	public:
		/**
		 * @brief Returns a reference to the core logger.
		 * @return A shared pointer to the core logger.
		 */
		static std::shared_ptr<spdlog::logger>& get_core_logger();
		/**
		 * @brief Returns a reference to the client logger.
		 * @return A shared pointer to the client logger.
		 */
		static std::shared_ptr<spdlog::logger>& get_client_logger();
	};
}

/**
 * @brief Macro for logging a message at the trace level for the core logger.
 * @details This macro logs a message at the trace level for the core logger.
 * @param[in] args The arguments to be passed to the logger.
 */
template<typename... Args> void TRIMANA_CORE_TRACE(Args&&... args) { trimana::core::logger::get_core_logger()->trace(std::forward<Args>(args)...); }

/**
 * @brief Macro for logging a message at the info level for the core logger.
 * @details This macro logs a message at the info level for the core logger.
 * @param[in] args The arguments to be passed to the logger.
 */
template<typename... Args> void TRIMANA_CORE_INFO(Args&&... args) { trimana::core::logger::get_core_logger()->info(std::forward<Args>(args)...); }

/**
 * @brief Macro for logging a message at the warn level for the core logger.
 * @details This macro logs a message at the warn level for the core logger.
 * @param[in] args The arguments to be passed to the logger.
 */
template<typename... Args> void TRIMANA_CORE_WARN(Args&&... args) { trimana::core::logger::get_core_logger()->warn(std::forward<Args>(args)...); }

/**
 * @brief Macro for logging a message at the error level for the core logger.
 * @details This macro logs a message at the error level for the core logger.
 * @param[in] args The arguments to be passed to the logger.
 */
template<typename... Args> void TRIMANA_CORE_ERROR(Args&&... args) { trimana::core::logger::get_core_logger()->error(std::forward<Args>(args)...); }

/**
 * @brief Macro for logging a message at the critical level for the core logger.
 * @details This macro logs a message at the critical level for the core logger.
 * @param[in] args The arguments to be passed to the logger.
 */
template<typename... Args> void TRIMANA_CORE_CRITICAL(Args&&... args) { trimana::core::logger::get_core_logger()->critical(std::forward<Args>(args)...); }


/**
 * @brief Macro for logging a message at the trace level for the client logger.
 * @details This macro logs a message at the trace level for the client logger.
 * @param[in] args The arguments to be passed to the logger.
 */
template<typename... Args> void TRIMANA_TRACE(Args&&... args) { trimana::core::logger::get_client_logger()->trace(std::forward<Args>(args)...); }

/**
 * @brief Macro for logging a message at the info level for the client logger.
 * @details This macro logs a message at the info level for the client logger.
 * @param[in] args The arguments to be passed to the logger.
 */
template<typename... Args> void TRIMANA_INFO(Args&&... args) { trimana::core::logger::get_client_logger()->info(std::forward<Args>(args)...); }

/**
 * @brief Macro for logging a message at the warn level for the client logger.
 * @details This macro logs a message at the warn level for the client logger.
 * @param[in] args The arguments to be passed to the logger.
 */
template<typename... Args> void TRIMANA_WARN(Args&&... args) { trimana::core::logger::get_client_logger()->warn(std::forward<Args>(args)...); }

/**
 * @brief Macro for logging a message at the error level for the client logger.
 * @details This macro logs a message at the error level for the client logger.
 * @param[in] args The arguments to be passed to the logger.
 */
template<typename... Args> void TRIMANA_ERROR(Args&&... args) { trimana::core::logger::get_client_logger()->error(std::forward<Args>(args)...); }

/**
 * @brief Macro for logging a message at the critical level for the client logger.
 * @details This macro logs a message at the critical level for the client logger.
 * @param[in] args The arguments to be passed to the logger.
 */
template<typename... Args> void TRIMANA_CRITICAL(Args&&... args) { trimana::core::logger::get_client_logger()->critical(std::forward<Args>(args)...); }
