#ifndef __DEV_LIB_DEV_HELPER_H__
#define __DEV_LIB_DEV_HELPER_H__

#include <stdint.h>
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
  typedef std::vector<std::string>    strings_type;

  static std::string format(const char* fmt, ...);
  static std::string formatEx(const char * fmt, va_list& args);
  static std::string getLine(std::istream& is);
  static unsigned int sum(const uints_type& value);
  static size_t count(const floats_type& source, float value, size_t start, size_t end);
  static std::tuple<bool, size_t> find(const floats_type& source, float value, size_t start = 0);
  static uints_type& append(const uints_type& source, uints_type& target);
  static uints_type& sort(uints_type& values);
  static uints_type& removeSame(uints_type& values);

  static std::string toString(float value);
  static std::string toString(bool value);
  static std::string toString(int value);
  static std::string toString(unsigned int value);
  static std::string toString(float value, size_t precision);
  static std::string toString(const uints_type& value, char flag = ',');
  static std::string toString(const floats_type& value, size_t precision = 1, char flag = ',');
  static std::string convertToHex(const uints_type& source);
  static std::string convertToHex(const std::string& source);
  static strings_type split(const char* value, const char delimiter = ',');
  static std::string merge(const char* begin, const char* end, const char delimiter = '~');

  static uint8_t getHigh(uint16_t value);
  static uint8_t getLow(uint16_t value);
  static uint8_t mergeTo8(uint8_t high, uint8_t low);
  static uint16_t mergeTo16(uint8_t high, uint8_t low);

  template <typename T>
  static std::string getType(const T& value);

public:
  static const float inf;
  static const char SPACE_FLAG;

private:
  static unsigned int getLength(const char * fmt, va_list& args);
  template <typename T>
  static T doMerge(uint8_t high, uint8_t low, uint8_t bitNum);
};

template <typename T>
inline std::string DevHelper::getType(const T& value)
{
  std::string result(typeid(value).name());
  return result.substr(result.find_first_not_of("0123456789"));
}

template <typename T>
inline T DevHelper::doMerge(uint8_t high, uint8_t low, uint8_t bitNum)
{
  return (high << bitNum) | low ;
}

#endif
