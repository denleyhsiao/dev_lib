#ifndef __DEV_LIB_LOG_LOG_HARNESS_H__
#define __DEV_LIB_LOG_LOG_HARNESS_H__

#include <string>
#include <memory>

class Log;
namespace Private
{
  enum LogLevel {LOG_DEBUG = 0, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FETAL};
  void init(std::shared_ptr<Log> log);
  void doLog(LogLevel level, const std::string& content, const char* fileName, unsigned int line);
  static std::shared_ptr<Log> log = nullptr;
}

#define LOG_INIT(log)      Private::init(log)
#define LOG_DESTROY()      Private::init(nullptr)
#define LOG_DEBUG(content) Private::doLog(Private::LOG_DEBUG, content, __FILE__, __LINE__)
#define LOG_INFO(content)  Private::doLog(Private::LOG_INFO,  content, __FILE__, __LINE__)
#define LOG_WARN(content)  Private::doLog(Private::LOG_WARN,  content, __FILE__, __LINE__)
#define LOG_ERROR(content) Private::doLog(Private::LOG_ERROR, content, __FILE__, __LINE__)
#define LOG_FETAL(content) Private::doLog(Private::LOG_FETAL, content, __FILE__, __LINE__)

#endif
