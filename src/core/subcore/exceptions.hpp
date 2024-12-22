#pragma once

#include <iostream>
#include <string_view>
#include <exception>
#include <source_location>

#include "base.hpp"

namespace trimana::core{

    class TRIMANA_API exception {
        public:
            exception() = default;
            virtual ~exception() = default;

            virtual const std::string_view& what() const noexcept = 0;
            virtual const std::source_location& location() const noexcept = 0;
    };

    class TRIMANA_API uninitialize_exception : public exception {
        public:
            uninitialize_exception(const std::string_view& message) : m_message(message), m_location(std::source_location::current()) {};
            uninitialize_exception(const std::string_view& message, const std::source_location location): m_message(message), m_location(location) {};
            virtual ~uninitialize_exception() = default;

            const std::string_view& what() const noexcept override {
                return m_message.data();
            }

            const std::source_location& location() const noexcept override {
                return m_location;
            }

        private:
            std::string_view m_message{};
            std::source_location m_location{};
    };

    class TRIMANA_API not_implemented_exception : public exception {
        public:
            not_implemented_exception(const std::string_view& message) : m_message(message), m_location(std::source_location::current()) {};
            not_implemented_exception(const std::string_view& message, const std::source_location location): m_message(message), m_location(location) {};
            virtual ~not_implemented_exception() = default;

            const std::string_view& what() const noexcept override {
                return m_message.data();
            }

            const std::source_location& location() const noexcept override {
                return m_location;
            }

        private:
            std::string_view m_message{};
            std::source_location m_location{};
    };

    class TRIMANA_API api_failure_exception : public exception {
        public:
            api_failure_exception(const std::string_view& message) : m_message(message), m_location(std::source_location::current()) {};
            api_failure_exception(const std::string_view& message, const std::source_location location): m_message(message), m_location(location) {};
            virtual ~api_failure_exception() = default;

            const std::string_view& what() const noexcept override {
                return m_message.data();
            }

            const std::source_location& location() const noexcept override {
                return m_location;
            }

        private:    
            std::string_view m_message{};
            std::source_location m_location{};    
    };
}