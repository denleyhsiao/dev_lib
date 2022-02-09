#include "dev_lib/message/comm_message.h"

CommMessage::CommMessage(HasInitCallback lpfnHasInit, ReInitCallback lpfnReInit,
  WriteCallback lpfnWrite, AsyncReadCallback lpfnAsyncRead, ReadCallback lpfnRead)
  : lpfnHasInit(lpfnHasInit), lpfnReInit(lpfnReInit),
  lpfnWrite(lpfnWrite), lpfnAsyncRead(lpfnAsyncRead), lpfnRead(lpfnRead)
{

}


bool CommMessage::hasInit() const
{
  if (lpfnHasInit)
    return lpfnHasInit();
  return false;
}

void CommMessage::reInit()
{
  if (lpfnReInit)
    lpfnReInit();
}

void CommMessage::write(const data_type& data)
{
  if (lpfnWrite)
    lpfnWrite(data);
}

void CommMessage::asyncRead(HandleAfterReadCallback lpfnHandleAfterRead)
{
  if (lpfnAsyncRead)
    lpfnAsyncRead(lpfnHandleAfterRead);
}

CommMessage::data_type CommMessage::read(size_t size) const
{
  data_type result = data_type();
  if (lpfnRead)
    result = lpfnRead(size);
  return result;
}
