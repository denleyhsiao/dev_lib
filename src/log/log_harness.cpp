#include "dev_lib/log/log_harness.h"
#include "dev_lib/log/log.h"
#include <cassert>

namespace Private
{
  void init(std::shared_ptr<Log> value)
  {
    log = value;
  }
  void doLog(LogLevel level, const std::string& content, const char* fileName, unsigned int line)
  {
    if (log == nullptr)
      return ;

    switch(level)
    {
      case LOG_DEBUG:
        log->debug(content, fileName, line);
        break;
      case LOG_INFO:
        log->info(content, fileName, line);
        break;
      case LOG_WARN:
        log->warn(content, fileName, line);
        break;
      case LOG_ERROR:
        log->error(content, fileName, line);
        break;
      case LOG_FETAL:
        log->fetal(content, fileName, line);
        break;
      default:
        assert(false);
        break;
    }
  }
}
