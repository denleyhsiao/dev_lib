#ifndef __DEV_LIG_LOG_CONSOLE_LOG__
#define __DEV_LIG_LOG_CONSOLE_LOG__

#include "dev_lib/log/log.h"
#include <memory>

class ConsoleLog : public Log
{
public:
  static std::shared_ptr<Log> create();
  ConsoleLog() { }
  virtual void debug(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__);
  virtual void info(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__);
  virtual void warn(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__);
  virtual void error(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__);
  virtual void fetal(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__);
};

#endif
