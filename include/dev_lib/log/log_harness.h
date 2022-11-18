#ifndef __DEV_LIB_LOG_LOG_HARNESS_H__
#define __DEV_LIB_LOG_LOG_HARNESS_H__

//为了防止windows.h头文件中的ERROR与glog的ERROR重定义问题.这个宏必须在包含logging.h之前定义!
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

class LogHarness
{
public:
  LogHarness(int argc, char** argv);
  ~LogHarness();
};

struct Precision
{
  friend std::ostream& operator<<(std::ostream& out, const Precision& value);
  Precision(float value, size_t precision = 3);
  float value;
  size_t precision;
};

struct Hex
{
  friend std::ostream& operator<<(std::ostream& out, const Hex& value);
  Hex(uint8_t value);
  uint8_t value;
};

std::ostream& operator<<(std::ostream& out, uint8_t value);

#endif
