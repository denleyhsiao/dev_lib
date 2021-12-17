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

#endif
