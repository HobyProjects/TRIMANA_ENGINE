#pragma once

#include <iostream>
#include <exception>
#include <string_view>
#include <source_location>

#include "base.hpp"
#include "log.hpp"

namespace trimana::core
{
	/**
	 * @brief Base class for exceptions in the core module.
	 */
	class exception
	{
	public:
		/**
		 * @brief Constructs an exception with the specified message and source location.
		 * @param message The exception message.
		 * @param location The source location where the exception occurred.
		 */
		exception(const std::string_view& message, const std::source_location location)
			: m_message(message), m_location(location) {}

		/**
		 * @brief Default destructor.
		 */
		virtual ~exception() = default;


		/**
		 * @brief Gets a string representation of the exception.
		 * @return The exception message.
		 */
		virtual void what() const noexcept {};

	protected:
		std::string_view m_message{};       /**< The exception message. */
		std::source_location m_location{};  /**< The source location where the exception occurred. */
	};

	/**
	 * @brief Exception class for uninitialized objects.
	 */
	class uninitialized_object_exception : public exception
	{
	public:
		/**
		 * @brief Constructs an uninitialized exception with the specified message and current source location.
		 * @param message The exception message.
		 */
		uninitialized_object_exception(const std::string_view& message) : exception(message, std::source_location::current()) {};

		/**
		 * @brief Constructs an uninitialized exception with the specified message and source location.
		 * @param message The exception message.
		 * @param location The source location where the exception occurred.
		 */
		uninitialized_object_exception(const std::string_view& message, const std::source_location location) : exception(message, location) {};

		/**
		 * @brief Default destructor.
		 */
		virtual ~uninitialized_object_exception() = default;


		/**
		 * @brief Gets a string representation of the exception.
		 * @return The exception message.
		 */
		void what() const noexcept override
		{
			TRIMANA_CRITICAL("Uninitialized object exception: {0} (in file:{1} | at line: {2})", m_message, m_location.file_name(), m_location.line());
			TRIMANA_DEBUGBREAK();
		}
	};

	/**
	 * @brief Exception class for not implemented functionality.
	 */
	class unimplemented_feature_exception : public exception
	{
	public:
		/**
		 * @brief Constructs a not implemented exception with the specified message and current source location.
		 * @param message The exception message.
		 */
		unimplemented_feature_exception(const std::string_view& message) : exception(message, std::source_location::current()) {};

		/**
		 * @brief Constructs a not implemented exception with the specified message and source location.
		 * @param message The exception message.
		 * @param location The source location where the exception occurred.
		 */
		unimplemented_feature_exception(const std::string_view& message, const std::source_location location) : exception(message, location) {};

		/**
		 * @brief Default destructor.
		 */
		virtual ~unimplemented_feature_exception() = default;

		/**
		 * @brief Gets a string representation of the exception.
		 * @return The exception message.
		 */
		void what() const noexcept override
		{
			TRIMANA_CRITICAL("Unimplemented feature exception: {0} (in file:{1} | at line: {2})", m_message, m_location.file_name(), m_location.line());
			TRIMANA_DEBUGBREAK();
		}
	};

	/**
	 * @brief Exception class for API failures.
	 */
	class api_response_exception : public exception
	{
	public:
		/**
		 * @brief Constructs an API failure exception with the specified message and current source location.
		 * @param message The exception message.
		 */
		api_response_exception(const std::string_view& message) : exception(message, std::source_location::current()) {};

		/**
		 * @brief Constructs an API failure exception with the specified message and source location.
		 * @param message The exception message.
		 * @param location The source location where the exception occurred.
		 */
		api_response_exception(const std::string_view& message, const std::source_location location) : exception(message, location) {};

		/**
		 * @brief Default destructor.
		 */
		virtual ~api_response_exception() = default;

		/**
		 * @brief Gets a string representation of the exception.
		 * @return The exception message.
		 */
		void what() const noexcept override
		{
			TRIMANA_CRITICAL("Api response exception : {0} (in file:{1} | at line: {2})", m_message, m_location.file_name(), m_location.line());
			TRIMANA_DEBUGBREAK();
		}
	};

	/**
	 * @brief Exception class for null pointers.
	 */
	class null_pointer_exception : public exception
	{
	public:
		/**
		 * @brief Constructs a null pointer exception with the specified message and current source location.
		 * @param message The exception message.
		 */
		null_pointer_exception(const std::string_view& message) : exception(message, std::source_location::current()) {};

		/**
		 * @brief Constructs a null pointer exception with the specified message and source location.
		 * @param message The exception message.
		 * @param location The source location where the exception occurred.
		 */
		null_pointer_exception(const std::string_view& message, const std::source_location location) : exception(message, location) {};

		/**
		 * @brief Default destructor.
		 */
		virtual ~null_pointer_exception() = default;

		/**
		 * @brief Gets a string representation of the exception.
		 * @return The exception message.
		 */
		void what() const noexcept override
		{
			TRIMANA_CRITICAL("Null pointer exception : {0} (in file:{1} | at line: {2})", m_message, m_location.file_name(), m_location.line());
			TRIMANA_DEBUGBREAK();
		}
	};
}