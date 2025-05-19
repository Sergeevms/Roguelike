#include "pch.h"
#include "Logger.h"

namespace MaxrEngine
{
    std::string LogSink::LogLevelToString(LogLevel logLevel)
    {
        switch (logLevel)
        {
        case LogLevel::INFO:
            return "[INFO]";
        case LogLevel::WARNING:
            return "[WARNING]";
        case LogLevel::ERROR:
            return "[ERROR]";
        default:
            return "[UNKNOWN]";
        }
    }

    void ConsoleSink::Log(LogLevel logLevel, const std::string& message)
    {
        std::cout << LogLevelToString(logLevel) << message << std::endl;
    }

    FileSink::FileSink(const std::string& fileName)
    {
        logFile.open(fileName, std::ios::app);
    }

    FileSink::~FileSink()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    void FileSink::Log(LogLevel logLevel, const std::string& message)
    {
        if (logFile.is_open())
        {
            logFile << message << std::endl;
        }
    }

    void Logger::AddSink(std::shared_ptr<LogSink> sink)
    {
        sinks.push_back(sink);
    }

    void Logger::Log(LogLevel logLevel, const std::string& message)
    {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto& sink : sinks)
        {
            sink->Log(logLevel, message);
        }
    }

    void Logger::Info(const std::string& message)
    {
        Log(LogLevel::INFO, message);
    }

    void Logger::Warn(const std::string& message)
    {
        Log(LogLevel::WARNING, message);
    }

    void Logger::Error(const std::string& message)
    {
        Log(LogLevel::ERROR, message);
    }

    std::shared_ptr<Logger> LoggerRegister::GetLogger(const std::string& name)
    {
        auto it = loggers.find(name);
        if (it != loggers.end())
        {
            return it->second;
        }
        return defaultLogger;
    }

    void LoggerRegister::SetDefaultLogger(std::shared_ptr<Logger> logger)
    {
        std::lock_guard<std::mutex> lock(mutex);
        defaultLogger = logger;
        bool registered = false;
        for (const auto& it : loggers)
        {
            if (logger == it.second)
            {
                registered = true;
                break;
            }
        }
        if (!registered)
        {
            loggers["Default"] = logger;
        }
    }

    void LoggerRegister::RegisterLogger(const std::string& name, std::shared_ptr<Logger> logger)
    {
        std::lock_guard<std::mutex> lock(mutex);
        loggers[name] = logger;
    }

    void LoggerRegister::UnregisterLogger(const std::string& name)
    {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = loggers.find(name);
        if (it != loggers.end())
        {
            loggers.erase(it);
        }
    }
}