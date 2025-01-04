#pragma once

#include <iostream>
#include <string_view>
#include <source_location>

#include "base.hpp"
#include "log.hpp"

namespace TE::Core
{
	class Exception
	{
		public:
			Exception(const std::string_view& message, const std::source_location location) : m_Message(message), m_SourceLocation(location) {}
			virtual ~Exception() = default;

			virtual void What() const noexcept {};

		protected:
			std::string_view m_Message{};    
			std::source_location m_SourceLocation{};  
	};

	class UninitializedObjectException : public Exception
	{
		public:
			UninitializedObjectException(const std::string_view& message) : Exception(message, std::source_location::current()) {};
			UninitializedObjectException(const std::string_view& message, const std::source_location location) : Exception(message, location) {};
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
		UnimplementedFeatureException(const std::string_view& message) : Exception(message, std::source_location::current()) {};
		UnimplementedFeatureException(const std::string_view& message, const std::source_location location) : Exception(message, location) {};
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
			BaseAPIException(const std::string_view& message) : Exception(message, std::source_location::current()) {};
			BaseAPIException(const std::string_view& message, const std::source_location location) : Exception(message, location) {};
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
		RenderingAPIException(const std::string_view& message) : Exception(message, std::source_location::current()) {};
		RenderingAPIException(const std::string_view& message, const std::source_location location) : Exception(message, location) {};
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
			NullPointerException(const std::string_view& message) : Exception(message, std::source_location::current()) {};
			NullPointerException(const std::string_view& message, const std::source_location location) : Exception(message, location) {};
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
		InvalidParameterException(const std::string_view& message) : Exception(message, std::source_location::current()) {};
		InvalidParameterException(const std::string_view& message, const std::source_location location) : Exception(message, location) {};
		virtual ~InvalidParameterException() = default;

		void What() const noexcept override
		{
			TE_CRITICAL("Invalid parameter exception : {0} (in file:{1} | at line: {2})", m_Message, m_SourceLocation.file_name(), m_SourceLocation.line());
			TE_DEBUGBREAK();
		}
	};

	class IOStreamException : public Exception
	{
	public:
		IOStreamException(const std::string_view& message) : Exception(message, std::source_location::current()) {};
		IOStreamException(const std::string_view& message, const std::source_location location) : Exception(message, location) {};
		virtual ~IOStreamException() = default;

		void What() const noexcept override
		{
			TE_CRITICAL("IO stream exception : {0} (in file:{1} | at line: {2})", m_Message, m_SourceLocation.file_name(), m_SourceLocation.line());
			TE_DEBUGBREAK();
		}
	};
}