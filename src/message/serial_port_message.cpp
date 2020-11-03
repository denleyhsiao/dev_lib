#include "dev_lib/message/serial_port_message.h"

SerialPortMessage::SerialPortMessage(HasInitCallback lpfnHasInit, ReInitCallback lpfnReInit,
  WriteCallback lpfnWrite, AsyncReadCallback lpfnAsyncRead, ReadCallback lpfnRead)
  : lpfnHasInit(lpfnHasInit), lpfnReInit(lpfnReInit),
  lpfnWrite(lpfnWrite), lpfnAsyncRead(lpfnAsyncRead), lpfnRead(lpfnRead)
{

}


bool SerialPortMessage::hasInit() const
{
  if (lpfnHasInit)
    return lpfnHasInit();
  return false;
}

void SerialPortMessage::reInit()
{
  if (lpfnReInit)
    lpfnReInit();
}

void SerialPortMessage::write(const data_type& data)
{
  if (lpfnWrite)
    lpfnWrite(data);
}

void SerialPortMessage::asyncRead(HandleAfterReadCallback lpfnHandleAfterRead, const data_type& delim)
{
  if (lpfnAsyncRead)
    lpfnAsyncRead(lpfnHandleAfterRead, delim);
}

SerialPortMessage::data_type SerialPortMessage::read(size_t size) const
{
  data_type result = data_type();
  if (lpfnRead)
    result = lpfnRead(size);
  return result;
}
