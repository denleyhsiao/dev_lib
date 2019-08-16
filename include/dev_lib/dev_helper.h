#ifndef __DEV_LIB_DEV_HELPER_H__
#define __DEV_LIB_DEV_HELPER_H__

#include <stdarg.h>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <typeinfo>

class DevHelper
{
public:
  typedef std::vector<unsigned char>  uints_type;
  typedef std::vector<float>          floats_type;

  static std::string format(const char* fmt, ...);
  static std::string getLine(std::istream& is);
  static unsigned int sum(const uints_type& value);
  static size_t count(const floats_type& source, float value, size_t start, size_t end);
  static std::tuple<bool, size_t> find(const floats_type& source, float value, size_t start = 0);
  static uints_type& append(const uints_type& source, uints_type& target);
  static uints_type& removeSame(uints_type& values);

  static std::string toString(float value);
  static std::string toString(bool value);
  static std::string toString(int value);
  static std::string toString(unsigned int value);
  static std::string toString(float value, size_t precision);
  static std::string toString(const uints_type& value, char flag = ',');
  static std::string toString(const floats_type& value, size_t precision = 1, char flag = ',');

  template <typename T>
  static std::string getType(const T& value);

public:
  static const float inf;
  static const char SPACE_FLAG;
private:
  static int vscprintf(const char * format, va_list args);
};

template <typename T>
inline std::string DevHelper::getType(const T& value)
{
  std::string result(typeid(value).name());
  return result.substr(result.find_first_not_of("0123456789"));
}

#endif
