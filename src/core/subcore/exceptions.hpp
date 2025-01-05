#pragma once

#include <iostream>
#include <string_view>
#include <source_location>
#include <spdlog/fmt/fmt.h>

#include "base.hpp"
#include "log.hpp"

namespace TE::Core
{
	class Exception
	{
		public:
			Exception(const std::string& message, const std::source_location location) 
				: m_Message(message), m_SourceLocation(location) {}
			virtual ~Exception() = default;

			virtual void What() const noexcept {}

		protected:
			std::string m_Message{};    
			std::source_location m_SourceLocation{};  
	};

	class UninitializedObjectException : public Exception
	{
		public:
			template<typename... Args>
			UninitializedObjectException(const std::string& message, const Args&&... args) 
				: Exception(fmt::format(message, std::forward<Args>(args)...), std::source_location::current()) {};
			virtual ~UninitializedObjectException() = default;

			void What() const noexcept override
			{
				TE_CRITICAL("Uninitialized object exception: {0} (in file:{1} | at line: {2})", m_Message, m_SourceLocation.file_name(), m_SourceLocation.line());
				TE_DEBUGBREAK();
			}
	};

	class UnimplementedFeatureException : public Exception
	{
		public:
			template<typename... Args>
			constexpr UnimplementedFeatureException(const std::string& message, const Args&&... args) 
				: Exception(fmt::format(message, std::forward<Args>(args)...), std::source_location::current()) {};
			virtual ~UnimplementedFeatureException() = default;

			void What() const noexcept override
			{
				TE_CRITICAL("Unimplemented feature exception: {0} (in file:{1} | at line: {2})", m_Message, m_SourceLocation.file_name(), m_SourceLocation.line());
				TE_DEBUGBREAK();
			}
	};

	class BaseAPIException : public Exception
	{
		public:
			template<typename... Args>
			constexpr BaseAPIException(const std::string& message, const Args&&... args)
				: Exception(fmt::format(message, std::forward<Args>(args)...), std::source_location::current()) {};
			virtual ~BaseAPIException() = default;

			void What() const noexcept override
			{
				TE_CRITICAL("Api response exception : {0} (in file:{1} | at line: {2})", m_Message, m_SourceLocation.file_name(), m_SourceLocation.line());
				TE_DEBUGBREAK();
			}
	};

	class RenderingAPIException : public Exception
	{
		public:
			template<typename... Args>
			constexpr RenderingAPIException(const std::string& message, const Args&&... args)
				: Exception(fmt::format(message, std::forward<Args>(args)...), std::source_location::current()) {};
			virtual ~RenderingAPIException() = default;

			void What() const noexcept override
			{
				TE_CRITICAL("Rendering API exception : {0} (in file:{1} | at line: {2})", m_Message, m_SourceLocation.file_name(), m_SourceLocation.line());
				TE_DEBUGBREAK();
			}
	};

	class NullPointerException : public Exception
	{
		public:
			template<typename... Args>
			constexpr NullPointerException(const std::string& message, const Args&&... args)
				: Exception(fmt::format(message, std::forward<Args>(args)...), std::source_location::current()) {};
			virtual ~NullPointerException() = default;

			void What() const noexcept override
			{
				TE_CRITICAL("Null pointer exception : {0} (in file:{1} | at line: {2})", m_Message, m_SourceLocation.file_name(), m_SourceLocation.line());
				TE_DEBUGBREAK();
			}
	};

	class InvalidParameterException : public Exception
	{
	public:
		template<typename... Args>
		constexpr InvalidParameterException(const std::string& message, const Args&&... args)
			: Exception(fmt::format(message, std::forward<Args>(args)...), std::source_location::current()) {};
		virtual ~InvalidParameterException() = default;

		void What() const noexcept override
		{
			TE_CRITICAL("Invalid parameter exception : {0} (in file:{1} | at line: {2})", m_Message, m_SourceLocation.file_name(), m_SourceLocation.line());
			TE_DEBUGBREAK();
		}
	};

	class IOException : public Exception
	{
	public:
		template<typename... Args>
		constexpr IOException(const std::string& message, const Args&&... args)
			: Exception(fmt::format(message, std::forward<Args>(args)...), std::source_location::current()) {};
		virtual ~IOException() = default;

		void What() const noexcept override
		{
			TE_CRITICAL("IO exception : {0} (in file:{1} | at line: {2})", m_Message, m_SourceLocation.file_name(), m_SourceLocation.line());
			TE_DEBUGBREAK();
		}
	};
}