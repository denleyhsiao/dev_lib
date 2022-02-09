#include "dev_lib/comm/tcp_comm.h"

bool TCPComm::init(const char* argv1, unsigned int argv2, HandleInitCallback lpfnHandleInit)
{
  message = lpfnHandleInit(argv1, argv2);
  return hasInit();
}
