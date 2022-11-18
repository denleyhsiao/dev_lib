#include "dev_lib/comm/common_comm.h"
#include "dev_lib/message/comm_message.h"

CommonComm::CommonComm() : message(nullptr)
{
}

bool CommonComm::hasInit() const
{
  return (message != nullptr && message->hasInit());
}

void CommonComm::reopen()
{
  message->reInit();
}

void CommonComm::doWrite(const data_type& data)
{
  message->write(data);
}

void CommonComm::asyncRead(HandleAfterReadCallback lpfnHandleAfterRead)
{
  message->asyncRead(lpfnHandleAfterRead);
}

CommonComm::data_type CommonComm::read(size_t size) const
{
  return message->read(size);
}
