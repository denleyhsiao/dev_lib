#ifndef __DEVLIB_LIB_COMM_TCP_COMM_H__
#define __DEVLIB_LIB_COMM_TCP_COMM_H__

#include "dev_lib/comm/common_comm.h"

class TCPComm : public CommonComm
{
public:
  virtual bool init(const char* argv1, unsigned int argv2, HandleInitCallback lpfnHandleInit) override;
};

#endif
