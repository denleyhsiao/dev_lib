#include "dev_lib/comm/mock_comm.h"

std::shared_ptr<Comm> MockComm::create(std::shared_ptr<Log> log)
{
  return std::shared_ptr<Comm>(new MockComm(log));
}

bool MockComm::init(const char* serialPort, unsigned int serialBaudrate)
{
  return true;
}

MockComm::data_type MockComm::read(size_t size) const
{
  return data_type();
}
