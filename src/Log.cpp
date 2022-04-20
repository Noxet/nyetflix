#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace NyetFlix
{
	std::shared_ptr<spdlog::logger> Log::s_coreLogger;


	void Log::init()
	{
		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_level(spdlog::level::warn);

		auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/nyetflix.txt", true);
		fileSink->set_level(spdlog::level::trace);

		spdlog::logger logger("NyetFlix", { consoleSink, fileSink });
		s_coreLogger = std::make_shared<spdlog::logger>(logger);
		s_coreLogger->set_level(spdlog::level::trace);
	}
}
