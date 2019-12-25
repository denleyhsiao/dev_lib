#ifndef __DEV_LIB_LOG_LOG_H__
#define __DEV_LIB_LOG_LOG_H__

#include <string>

enum LogLevel {LOG_DEBUG = 0, LOG_INFO = 1, LOG_ERROR = 2};

class Log
{
public:
  virtual ~Log() {}
  virtual void debug(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__) = 0;
  virtual void info(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__) = 0;
  virtual void warn(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__) = 0;
  virtual void error(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__) = 0;
  virtual void fetal(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__) = 0;
};

#endif
