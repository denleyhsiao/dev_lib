#include "dev_lib/log/console_log.h"
#include <iostream>

std::shared_ptr<Log> ConsoleLog::create()
{
  return std::shared_ptr<Log>(new ConsoleLog());
}

void ConsoleLog::debug(const std::string& message, const char* fileName /* = __FILE__ */, unsigned int line /* = __LINE__ */)
{
  std::cout<<message<<std::endl;
}

void ConsoleLog::info(const std::string& message, const char* fileName /* = __FILE__ */, unsigned int line /* = __LINE__ */)
{
  std::cout<<message<<std::endl;
}

void ConsoleLog::warn(const std::string& message, const char* fileName /* = __FILE__ */, unsigned int line /* = __LINE__ */)
{
  std::cout<<message<<std::endl;
}

void ConsoleLog::error(const std::string& message, const char* fileName /* = __FILE__ */, unsigned int line /* = __LINE__ */)
{
  std::cout<<message<<std::endl;
}

void ConsoleLog::fetal(const std::string& message, const char* fileName /* = __FILE__ */, unsigned int line /* = __LINE__ */)
{
  std::cout<<message<<std::endl;
}
