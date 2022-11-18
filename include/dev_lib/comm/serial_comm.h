#ifndef __DEV_LIB_COMM_SERIAL_COMM_H__
#define __DEV_LIB_COMM_SERIAL_COMM_H__

#include "dev_lib/comm/common_comm.h"

class SerialComm : public CommonComm
{
public:
  virtual bool init(const char* argv1, unsigned int argv2, HandleInitCallback lpfnHandleInit) override;
};

#endif
