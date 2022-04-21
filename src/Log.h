#pragma once

#include "spdlog/spdlog.h"

namespace NyetFlix
{
	class Log
	{
		static std::shared_ptr<spdlog::logger> s_coreLogger;

	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
	};
}


#define NF_CORE_TRACE(...)	::NyetFlix::Log::getCoreLogger()->trace(__VA_ARGS__)
#define NF_CORE_INFO(...)	::NyetFlix::Log::getCoreLogger()->info(__VA_ARGS__)
#define NF_CORE_WARN(...)	::NyetFlix::Log::getCoreLogger()->warn(__VA_ARGS__)
#define NF_CORE_ERROR(...)	::NyetFlix::Log::getCoreLogger()->error(__VA_ARGS__)
#define NF_CORE_FATAL(...)	::NyetFlix::Log::getCoreLogger()->fatal(__VA_ARGS__)
