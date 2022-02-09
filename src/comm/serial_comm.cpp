#include "dev_lib/comm/serial_comm.h"
#include "dev_lib/dev_helper.h"
#include "dev_lib/log/log_harness.h"

bool SerialComm::init(const char* argv1, unsigned int argv2, HandleInitCallback lpfnHandleInit)
{
  if (system(DevHelper::format("sudo chmod 666 %s", argv1).c_str()) == 0)
    message = lpfnHandleInit(argv1, argv2);
  else
    LOG(ERROR) << "Unable to sudo chmod 666 " << argv1;
  return hasInit();
}
