#ifndef __DEV_LIB_LOG_EMPTY_LOG_H__
#define __DEV_LIB_LOG_EMPTY_LOG_H__

#include "dev_lib/log/log.h"
#include <memory>

class EmptyLog : public Log
{
public:
  static std::shared_ptr<Log> create() { return std::shared_ptr<Log>(new EmptyLog()); }
  virtual void debug(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__) {}
  virtual void info(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__) {}
  virtual void warn(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__) {}
  virtual void error(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__) {}
  virtual void fetal(const std::string& message, const char* fileName = __FILE__, unsigned int line = __LINE__) {}

private:
  EmptyLog() {}
};

#endif
