#include "dev_lib/dev_helper.h"
#include <numeric>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>

const float DevHelper::inf = std::numeric_limits<float>::infinity();
const char DevHelper::SPACE_FLAG = ' ';

int DevHelper::vscprintf(const char * format, va_list args)
{
  va_list tempArgs;
  va_copy(tempArgs, args);
  int result = vsnprintf(nullptr, 0, format, tempArgs);
  va_end(tempArgs);
  return result;
}

std::string DevHelper::format(const char* fmt, ...)
{
  std::string result = "";
  va_list args;
  va_start(args, fmt);
  {
    int nLength = vscprintf(fmt, args) + 1;
    std::vector<char> temp(nLength);
    vsnprintf(temp.data(), nLength, fmt, args);
    result.assign(temp.data());
  }
  va_end(args);
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

DevHelper::uints_type& DevHelper::removeSame(uints_type& values)
{
  std::sort( values.begin(), values.end() );
  values.erase( std::unique( values.begin(), values.end() ), values.end() );
  return values;
}

std::string DevHelper::toString(float value, size_t precision /* = 1*/)
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

std::string DevHelper::getArg(unsigned int argc, char** argv, unsigned int index, const char* defaultValue /* = "" */)
{
  return (argc > index ? argv[index] : defaultValue);
}

unsigned int DevHelper::getArg(unsigned int argc, char** argv, unsigned int index, unsigned int defaultValue /* = 0 */)
{
  return (argc > index ? atoi(argv[index]) : defaultValue);
}

float DevHelper::getArg(unsigned int argc, char** argv, unsigned int index, float defaultValue /*= 0.0f */)
{
  return (argc > index ? atof(argv[index]) : defaultValue);
}

bool DevHelper::getArg(unsigned int argc, char** argv, unsigned int index, bool defaultValue /*= false */)
{
  return getArg(argc, argv, index, defaultValue ? "true" : "false") == "true";
}
