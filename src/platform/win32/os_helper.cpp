#include "dev_lib/os_helper.h"
#include <windows.h>

std::string OSHelper::getAppFileName()
{
  char result[MAX_PATH + 1] = "\0";
  DWORD retSize = GetModuleFileNameA(NULL, result, MAX_PATH);
  assert(retSize != 0);
  return result;
}
