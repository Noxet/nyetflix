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