#include "dev_lib/dev_helper.h"
#include <boost/lexical_cast.hpp>
#include <iterator>
#include <algorithm>
#include <unistd.h>
#include <limits.h>
#include <cassert>

int DevHelper::vscprintf(const char * format, va_list args)
{
  va_list tempArgs;
  va_copy(tempArgs, args);
  int result = vsnprintf(NULL, 0, format, tempArgs);
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

std::string DevHelper::getModuleFileName()
{
  char result[PATH_MAX + 1] = {0};
  int retValue = readlink(format("/proc/%d/exe", getpid()).c_str(), result, PATH_MAX);
  assert(retValue != -1);
  return result;
}

DevHelper::floats_type DevHelper::split(const char* value, const char delimiter /* = ',' */)
{
  static const char SPACE_FLAG = ' ';
  floats_type result = floats_type();
  std::string source = value;
  if (delimiter != SPACE_FLAG)
    std::replace(source.begin(), source.end(), delimiter, SPACE_FLAG);

  std::istringstream iss(source);
  std::vector<std::string> values((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
  for (std::string value: values)
    result.push_back(boost::lexical_cast<float>(value));
  return result;
}
