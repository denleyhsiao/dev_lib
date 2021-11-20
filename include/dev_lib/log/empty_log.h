#ifndef __DEV_LIB_LOG_EMPTY_LOG_H__
#define __DEV_LIB_LOG_EMPTY_LOG_H__

#include "dev_lib/log/log.h"
#include <memory>

class EmptyLog : public Log
{
public:
  static std::shared_ptr<Log> create() { return std::make_shared<EmptyLog>(); }
  EmptyLog() {}
  virtual void debug(const std::string& message, const char* fileName, unsigned int line) {}
  virtual void info(const std::string& message, const char* fileName, unsigned int line) {}
  virtual void warn(const std::string& message, const char* fileName, unsigned int line) {}
  virtual void error(const std::string& message, const char* fileName, unsigned int line) {}
  virtual void fetal(const std::string& message, const char* fileName, unsigned int line) {}
};

#endif
