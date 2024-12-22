#pragma once

#include <iostream>
#include <exception>
#include <string_view>
#include <source_location>

#include "base.hpp"

namespace trimana::core{

    class exception {
        public:
            exception(const std::string_view& message, const std::source_location location)
                : m_message(message), m_location(location) {}
            virtual ~exception() = default;

            virtual const std::string_view& what() const noexcept {};
            virtual const std::source_location& location() const noexcept {};

        protected:
            std::string_view m_message{};
            std::source_location m_location{};
    };

    class uninitialize_exception : public exception {
            uninitialize_exception(const std::string_view& message) : exception(message, std::source_location::current()) {};
            uninitialize_exception(const std::string_view& message, const std::source_location location): exception(message, location) {};
            virtual ~uninitialize_exception() = default;

            const std::string_view& what() const noexcept override {
                return m_message.data();
            }

            const std::source_location& location() const noexcept override {
                return m_location;
            }
    };

    class not_implemented_exception : public exception {
            not_implemented_exception(const std::string_view& message) : exception(message, std::source_location::current()) {};
            not_implemented_exception(const std::string_view& message, const std::source_location location): exception(message, location) {};
            virtual ~not_implemented_exception() = default;

            const std::string_view& what() const noexcept override {
                return m_message.data();
            }

            const std::source_location& location() const noexcept override {
                return m_location;
            }
    };

    class api_failure_exception : public exception {
            api_failure_exception(const std::string_view& message) : exception(message, std::source_location::current()) {};
            api_failure_exception(const std::string_view& message, const std::source_location location): exception(message, location) {};
            virtual ~api_failure_exception() = default;

            const std::string_view& what() const noexcept override {
                return m_message.data();
            }

            const std::source_location& location() const noexcept override {
                return m_location;
            }   
    };
}