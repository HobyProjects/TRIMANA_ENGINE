#pragma once

#include <iostream>
#include <exception>
#include <string_view>
#include <source_location>

#include "log.hpp"

namespace trimana::core{

    /**
     * @brief Base class for exceptions in the core module.
     */
    class exception {
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
    class uninitialize_exception : public exception {
        public:
            /**
             * @brief Constructs an uninitialized exception with the specified message and current source location.
             * @param message The exception message.
             */
            uninitialize_exception(const std::string_view& message) : exception(message, std::source_location::current()) {};

            /**
             * @brief Constructs an uninitialized exception with the specified message and source location.
             * @param message The exception message.
             * @param location The source location where the exception occurred.
             */
            uninitialize_exception(const std::string_view& message, const std::source_location location): exception(message, location) {};

            /**
             * @brief Default destructor.
             */
            virtual ~uninitialize_exception() = default;


            /**
             * @brief Gets a string representation of the exception.
             * @return The exception message.
             */
            void what() const noexcept override {
                TRIMANA_CRITICAL("Uninitialized exception: {0} (in file:{1} | at line: {2})", m_message, m_location.file_name(), m_location.line());
            }
    };

    /**
     * @brief Exception class for not implemented functionality.
     */
    class not_implemented_exception : public exception {
        public:
            /**
             * @brief Constructs a not implemented exception with the specified message and current source location.
             * @param message The exception message.
             */
            not_implemented_exception(const std::string_view& message) : exception(message, std::source_location::current()) {};

            /**
             * @brief Constructs a not implemented exception with the specified message and source location.
             * @param message The exception message.
             * @param location The source location where the exception occurred.
             */
            not_implemented_exception(const std::string_view& message, const std::source_location location): exception(message, location) {};

            /**
             * @brief Default destructor.
             */
            virtual ~not_implemented_exception() = default;

            /**
             * @brief Gets a string representation of the exception.
             * @return The exception message.
             */
            void what() const noexcept override {
                TRIMANA_CRITICAL("not_implemented_exception: {0} (in file:{1} | at line: {2})", m_message, m_location.file_name(), m_location.line());
            }
    };

    /**
     * @brief Exception class for API failures.
     */
    class api_failure_exception : public exception {
        public:
            /**
             * @brief Constructs an API failure exception with the specified message and current source location.
             * @param message The exception message.
             */
            api_failure_exception(const std::string_view& message) : exception(message, std::source_location::current()) {};

            /**
             * @brief Constructs an API failure exception with the specified message and source location.
             * @param message The exception message.
             * @param location The source location where the exception occurred.
             */
            api_failure_exception(const std::string_view& message, const std::source_location location): exception(message, location) {};

            /**
             * @brief Default destructor.
             */
            virtual ~api_failure_exception() = default;

            /**
             * @brief Gets a string representation of the exception.
             * @return The exception message.
             */
            void what() const noexcept override {
                TRIMANA_CRITICAL("api_failure_exception : {0} (in file:{1} | at line: {2})", m_message, m_location.file_name(), m_location.line());
            }
    };
}