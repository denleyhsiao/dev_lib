#ifndef __DEV_LIB_DEV_HELPER_H__
#define __DEV_LIB_DEV_HELPER_H__

#include <stdarg.h>
#include <string>

class DevHelper
{
public:
  static std::string format(const char* fmt, ...);
  
private:
  static int vscprintf(const char * format, va_list args);
};

#endif
