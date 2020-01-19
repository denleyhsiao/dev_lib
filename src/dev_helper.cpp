#include "dev_lib/dev_helper.h"
#include <iterator>
#include <sstream>
#include <numeric>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>

const float DevHelper::inf = std::numeric_limits<float>::infinity();
const char DevHelper::SPACE_FLAG = ' ';

std::string DevHelper::format(const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  std::string result = formatEx(fmt, args);
  va_end(args);
  return result;
}

std::string DevHelper::formatEx(const char * fmt, va_list& args)
{
  int length = getLength(fmt, args) + 1;
  std::vector<char> result(length);
  vsnprintf(result.data(), length, fmt, args);
  return result.data();
}

unsigned int DevHelper::getLength(const char * fmt, va_list& args)
{
  va_list tempArgs;
  va_copy(tempArgs, args);
  unsigned int result = vsnprintf(nullptr, 0, fmt, tempArgs);
  va_end(tempArgs);
  return result;
}

std::string DevHelper::getLine(std::istream& is)
{
  std::string result("");
  return (std::getline(is, result) ? result : "");
}

unsigned int DevHelper::sum(const uints_type& value)
{
  return std::accumulate(value.begin(), value.end(), 0);
}

size_t DevHelper::count(const floats_type& source, float value, size_t start, size_t end)
{
  return std::count(std::next(source.begin(), start), std::next(source.begin(), end), value);
}

std::tuple<bool, size_t> DevHelper::find(const floats_type& source, float value, size_t start /* = 0*/)
{
  auto pos = std::find(std::next(source.begin(), start), source.end(), value);
  bool hasFind = (pos != source.end());
  size_t result = hasFind ? std::distance(source.begin(), pos) : 0;
  return std::make_tuple(hasFind, result);
}

DevHelper::uints_type& DevHelper::append(const uints_type& source, uints_type& target)
{
  target.reserve(target.size() + source.size());
  target.insert(target.end(), source.begin(), source.end());
  return target;
}

DevHelper::uints_type& DevHelper::sort(uints_type& values)
{
  std::sort(values.begin(), values.end());
  return values;
}

DevHelper::uints_type& DevHelper::removeSame(uints_type& values)
{
  sort(values);
  values.erase(std::unique(values.begin(), values.end()), values.end());
  return values;
}

std::string DevHelper::toString(float value)
{
  return toString(value, 3);
}

std::string DevHelper::toString(bool value)
{
  return (value ? "true" : "false");
}

std::string DevHelper::toString(int value)
{
  return format("%d", value);
}

std::string DevHelper::toString(unsigned int value)
{
  return toString(static_cast<int>(value));
}

std::string DevHelper::toString(float value, size_t precision)
{
  std::stringstream ss;
  ss << std::fixed << std::setprecision(precision) << value;
  return ss.str();
}

std::string DevHelper::toString(const uints_type& value, char flag /* = ',' */)
{
  assert(!value.empty());
  return std::accumulate(std::next(value.begin()), value.end(),
                                  std::to_string(value[0]), // 以首元素开始
                                  [flag](std::string a, uint8_t b) {
                                    return a + std::string(1, flag) + std::to_string(b);
                                  });
}

std::string DevHelper::toString(const floats_type& value, size_t precision /* = 1 */, char flag /* = ',' */)
{
  assert(!value.empty());
  return std::accumulate(std::next(value.begin()), value.end(),
                                  toString(value[0], precision), // 以首元素开始
                                  [precision, flag](std::string a, float b) {
                                    return a + std::string(1, flag) + toString(b, precision);
                                  });
}

DevHelper::strings_type DevHelper::split(const char* value, const char delimiter /* = ',' */)
{
  strings_type result = strings_type();
  std::string source = value;
  if (delimiter != SPACE_FLAG)
    std::replace(source.begin(), source.end(), delimiter, DevHelper::SPACE_FLAG);

  std::istringstream iss(source);
  std::for_each(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
    [&result](const std::string& value){ result.push_back(value); });
  return result;
}

std::string DevHelper::merge(const char* begin, const char* end, const char delimiter /* = '~' */)
{
  return format("%s%c%s", begin, delimiter, end);
}


std::string DevHelper::convertToHex(const uints_type& source)
{
  char result[128] = {0x00};
  size_t size = source.size();
  for (size_t index = 0; index < size; ++index)
  {
    sprintf(&result[2*index], "%02X", source[index]);
  }
  return result;
}

std::string DevHelper::convertToHex(const std::string& source)
{
  static const char* const lut = "0123456789ABCDEF";
  size_t len = source.length();
  std::string result;
  result.reserve(2 * len);
  for (size_t index = 0; index < len; ++index)
  {
    const unsigned char c = source[index];
    result.push_back(lut[c >> 4]);
    result.push_back(lut[c & 15]);
  }
  return result;
}

uint8_t DevHelper::getHigh(uint8_t value)
{
  return value >> 4;
}

uint8_t DevHelper::getLow(uint8_t value)
{
  return value & 0x0F;
}

uint8_t DevHelper::getHigh(uint16_t value)
{
   return static_cast<uint8_t>(value >> 8);
}

uint8_t DevHelper::getLow(uint16_t value)
{
  return static_cast<uint8_t>(value & 0xFF);
}

uint8_t DevHelper::mergeTo8(uint8_t high, uint8_t low)
{
  assert(high < 0x10 && low < 0x10);
  return doMerge<uint8_t>(high, low, 4);
}

uint16_t DevHelper::mergeTo16(uint8_t high, uint8_t low)
{
  return doMerge<uint16_t>(high, low, 8);
}
