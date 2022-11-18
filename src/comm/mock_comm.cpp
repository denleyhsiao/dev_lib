#include "dev_lib/comm/mock_comm.h"

bool MockComm::init(const char* argv1, unsigned int argv2, HandleInitCallback lpfnHandleInit)
{
  return true;
}

MockComm::data_type MockComm::read(size_t size) const
{
  return data_type();
}
