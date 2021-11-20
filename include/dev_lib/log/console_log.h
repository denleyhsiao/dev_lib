#ifndef __DEV_LIG_LOG_CONSOLE_LOG__
#define __DEV_LIG_LOG_CONSOLE_LOG__

#include "dev_lib/log/log.h"
#include <memory>

class ConsoleLog : public Log
{
public:
  static std::shared_ptr<Log> create();
  ConsoleLog() { }
  virtual void debug(const std::string& message, const char* fileName, unsigned int line);
  virtual void info(const std::string& message, const char* fileName, unsigned int line);
  virtual void warn(const std::string& message, const char* fileName, unsigned int line);
  virtual void error(const std::string& message, const char* fileName, unsigned int line);
  virtual void fetal(const std::string& message, const char* fileName, unsigned int line);
};

#endif
