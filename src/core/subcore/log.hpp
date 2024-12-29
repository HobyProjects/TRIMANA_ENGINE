#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "base.hpp"

namespace TE::Core
{
	class Logger
	{
		private:
			Logger() = default;
			~Logger() = default;

		public:
			static std::shared_ptr<spdlog::logger>& CoreLogger();
			static std::shared_ptr<spdlog::logger>& EngineLogger();
	};
}

#define TE_CORE_TRACE(...) TE::Core::Logger::CoreLogger()->trace(__VA_ARGS__)
#define TE_CORE_INFO(...) TE::Core::Logger::CoreLogger()->info(__VA_ARGS__)
#define TE_CORE_WARN(...) TE::Core::Logger::CoreLogger()->warn(__VA_ARGS__)
#define TE_CORE_ERROR(...) TE::Core::Logger::CoreLogger()->error(__VA_ARGS__)
#define TE_CORE_CRITICAL(...) TE::Core::Logger::CoreLogger()->critical(__VA_ARGS__) 

#define TE_TRACE(...) TE::Core::Logger::EngineLogger()->trace(__VA_ARGS__)
#define TE_INFO(...) TE::Core::Logger::EngineLogger()->info(__VA_ARGS__)
#define TE_WARN(...) TE::Core::Logger::EngineLogger()->warn(__VA_ARGS__)
#define TE_ERROR(...) TE::Core::Logger::EngineLogger()->error(__VA_ARGS__)
#define TE_CRITICAL(...) TE::Core::Logger::EngineLogger()->critical(__VA_ARGS__) 
