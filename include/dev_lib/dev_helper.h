#ifndef __DEV_LIB_DEV_HELPER_H__
#define __DEV_LIB_DEV_HELPER_H__

#include <stdarg.h>
#include <string>
#include <sstream>
#include <vector>

class DevHelper
{
public:
  typedef std::vector<float>      floats_type;
  typedef std::vector<unsigned char> uints_type;
  static std::string format(const char* fmt, ...);
  static std::string getLine(std::istream& is);
  static std::string toString(float value, size_t precision = 1);
  static std::string toString(const uints_type& value, char flag = ',');
  static std::string toString(const floats_type& value, size_t precision = 1, char flag = ',');
  static std::string getArg(unsigned int argc, char** argv, unsigned int index, const char* defaultValue = "");
  static unsigned int getArg(unsigned int argc, char** argv, unsigned int index, unsigned int defaultValue = 0);
  static float getArg(unsigned int argc, char** argv, unsigned int index, float defaultValue = 0.0f);
  static bool getArg(unsigned int argc, char** argv, unsigned int index, bool defaultValue = false);

private:
  static int vscprintf(const char * format, va_list args);
};

#endif
