#ifndef __DEV_LIB_DEV_HELPER_H__
#define __DEV_LIB_DEV_HELPER_H__

#include <stdarg.h>
#include <string>
#include <vector>

class DevHelper
{
public:
  typedef std::vector<float>  floats_type;
  static std::string format(const char* fmt, ...);
  static std::string getLine(std::istream& is);
  static std::string getModuleFileName();
  static floats_type split(const char* value, const char delimiter = ',');

private:
  static int vscprintf(const char * format, va_list args);
};

#endif
