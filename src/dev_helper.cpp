#include "dev_lib/dev_helper.h"
#include <string.h>
#include <stdio.h>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <random>
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

DevHelper::size_type DevHelper::count(const floats_type& source, float value, size_type startIndex, size_type endIndex)
{
  assert(startIndex <= endIndex);
  return std::count(std::next(source.begin(), startIndex), std::next(source.begin(), endIndex), value);
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

DevHelper::uints_type& DevHelper::increase(uints_type& source, size_type index)
{
  std::for_each(source.begin(), source.end(), [index](value_type& value) { value += index; });
  return source;
}

DevHelper::uints_type& DevHelper::removeSame(uints_type& values)
{
  sort(values);
  values.erase(std::unique(values.begin(), values.end()), values.end());
  return values;
}

DevHelper::uints_type DevHelper::getChild(const uints_type& source, size_type start, size_type length)
{
  return uints_type(source.begin() + start, source.begin() + start + length);
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
                                  [flag](std::string a, value_type b) {
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

std::string DevHelper::toHex(const uints_type& source)
{
  std::stringstream ss;
  for (const auto& child : source)
    doToHex(ss, child);
  return ss.str();
}

std::string DevHelper::toHex(const char* source)
{
  return toHex(std::string(source, strlen(source)));
}

DevHelper::value_type DevHelper::crc(const value_type& cmd, const uints_type& data)
{
  value_type result = cmd;
  result ^= data.size();
  for (const auto& child : data)
    result ^= child;
  result &= 0x7F;
  return result;
}

DevHelper::value_type DevHelper::getHigh(value_type value)
{
  return value >> 4;
}

DevHelper::value_type DevHelper::getLow(value_type value)
{
  return value & 0x0F;
}

DevHelper::value_type DevHelper::getHigh(uint16_t value)
{
   return static_cast<value_type>(value >> 8);
}

DevHelper::value_type DevHelper::getLow(uint16_t value)
{
  return static_cast<value_type>(value & 0xFF);
}

DevHelper::value_type DevHelper::mergeTo8(value_type high, value_type low)
{
  assert(high < 0x10 && low < 0x10);
  return doMerge<value_type>(high, low, 4);
}

uint16_t DevHelper::mergeTo16(value_type high, value_type low)
{
  return doMerge<uint16_t>(high, low, 8);
}

DevHelper::BYTE* DevHelper::genRandom(BYTE* source, size_type length, BYTE minValue /* = 1*/, BYTE maxValue /* = 255*/)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(minValue, maxValue);

  for(size_type index = 0; index < length; ++index)
    source[index] = dis(gen);
  return source;
}

bool DevHelper::saveBinFile(const char* name, void* source, size_type length)
{
  FILE*  file= fopen(name, "wb");
  bool result = (file != nullptr);
  if(result)
  {
    fwrite(source, length, 1, file);
    fclose(file);
  }
  return result;
}

bool DevHelper::readBinFile(const char* name, void* source, size_type length)
{
  FILE* file = fopen(name, "rb");
  bool result = (file != nullptr);
  if(result)
  {
    fread(source, length, 1, file);
    fclose(file);
  }
  return result;
}

std::string DevHelper::toHex(BYTE* source, size_type length, size_t lineCount /* = 16 */)
{
  std::stringstream ss;
  for(size_type index = 0; index < length;)
  {
    doToHex(ss << "0x", source[index]);
    if (++index == length)
      ss << std::endl;
    else
    {
      ss << ", ";
      if (index % lineCount == 0)
        ss << std::endl;
    }
  }
  return ss.str();
}
