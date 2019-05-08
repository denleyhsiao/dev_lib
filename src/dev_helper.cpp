#include "dev_lib/dev_helper.h"
#include <vector>

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
