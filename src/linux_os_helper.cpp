#include "dev_lib/os_helper.h"
#include "dev_lib/dev_helper.h"
#include <unistd.h>
#include <limits.h>
#include <cassert>

std::string OSHelper::getModuleFileName()
{
  char result[PATH_MAX + 1] = {0};
  int retValue = readlink(DevHelper::format("/proc/%d/exe", getpid()).c_str(), result, PATH_MAX);
  assert(retValue != -1);
  return result;
}
