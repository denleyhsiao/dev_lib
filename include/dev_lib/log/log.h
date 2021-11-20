#ifndef __DEV_LIB_LOG_LOG_H__
#define __DEV_LIB_LOG_LOG_H__

#include <string>

class Log
{
public:
  virtual ~Log() {}
  virtual void debug(const std::string& message, const char* fileName, unsigned int line) = 0;
  virtual void info(const std::string& message, const char* fileName, unsigned int line) = 0;
  virtual void warn(const std::string& message, const char* fileName, unsigned int line) = 0;
  virtual void error(const std::string& message, const char* fileName, unsigned int line) = 0;
  virtual void fetal(const std::string& message, const char* fileName, unsigned int line) = 0;
};

#endif
