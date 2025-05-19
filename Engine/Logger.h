#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <mutex>
#include <unordered_map>
#include "EngineAPI.h"

namespace MaxrEngine
{
	enum LogLevel
	{
		INFO = 1,
		WARNING = 2,
		ERROR = 4,
		ALL = INFO | WARNING | ERROR
	};

	class LogSink
	{
	public:
		virtual void Log(LogLevel logLevel, const std::string& message) = 0;
		void ENGINE_API SetLoggedLevels(LogLevel newLoggingLevels);
		virtual ~LogSink() = default;
	protected:
		std::string LogLevelToString(LogLevel logLevel);
		LogLevel loggingLevels = LogLevel::ALL;
	};

	class ConsoleSink : public LogSink
	{
	public:
		ENGINE_API virtual void Log(LogLevel logLevel, const std::string& message) override;
	};
		
	class FileSink : public LogSink
	{
	public:
		ENGINE_API FileSink(const std::string& fileName);
		ENGINE_API ~FileSink();
		ENGINE_API virtual void Log(LogLevel logLevel, const std::string& message) override;
	private:
		std::ofstream logFile;
	};

	class Logger
	{
	public:
		void ENGINE_API AddSink(std::shared_ptr<LogSink> sink);
		void ENGINE_API Log(LogLevel logLevel, const std::string& message);
		void ENGINE_API Info(const std::string& message);
		void ENGINE_API Warn(const std::string& message);
		void ENGINE_API Error(const std::string& message);
		void ENGINE_API SetLoggedLevels(LogLevel newLoggingLevels);
	private:
		std::vector<std::shared_ptr<LogSink>> sinks;
		LogLevel loggingLevels = LogLevel::ALL;
		std::mutex mutex;
	};

	class LoggerRegister
	{
	public:
		ENGINE_API static LoggerRegister& GetInstance()
		{
			static LoggerRegister instance;
			return instance;
		}

		ENGINE_API std::shared_ptr<Logger> GetLogger(const std::string& name);
		ENGINE_API void SetDefaultLogger(std::shared_ptr<Logger> logger);
		ENGINE_API void RegisterLogger(const std::string& name, std::shared_ptr<Logger> logger);
		ENGINE_API void UnregisterLogger(const std::string& name);
	private:
		LoggerRegister() = default;
		LoggerRegister(const LoggerRegister&) = delete;
		LoggerRegister& operator=(const LoggerRegister&) = delete;
		std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
		std::shared_ptr<Logger> defaultLogger = std::make_shared<Logger>();
		std::mutex mutex;
	};
}

#define LOG_INFO(message) MaxrEngine::LoggerRegister::GetInstance().GetLogger("Global")->Info(message);
#define LOG_WARN(message) MaxrEngine::LoggerRegister::GetInstance().GetLogger("Global")->Warn(message);
#define LOG_ERROR(message) MaxrEngine::LoggerRegister::GetInstance().GetLogger("Global")->Error(message);