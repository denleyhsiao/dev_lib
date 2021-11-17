#include "dev_lib/comm/serial_port.h"
#include "dev_lib/dev_helper.h"
#include "dev_lib/log/log.h"
#include "dev_lib/message/serial_port_message.h"

SerialPort::SerialPort(std::shared_ptr<Log> log) : Comm(log), message(nullptr)
{
}

bool SerialPort::init(const char* port, unsigned int baudrate, HandleInitCallback lpfnHandleInit)
{
  if (system(DevHelper::format("sudo chmod 666 %s", port).c_str()) == 0)
    message = lpfnHandleInit(port, baudrate);
  else
    log->error(DevHelper::format("Unable to sudo chmod 666 %s", port));
  return hasInit();
}

bool SerialPort::hasInit() const
{
  return (message != nullptr && message->hasInit());
}

void SerialPort::reopen()
{
  message->reInit();
}

void SerialPort::doWrite(const data_type& data)
{
  message->write(data);
}

void SerialPort::asyncRead(HandleAfterReadCallback lpfnHandleAfterRead, const data_type& delim)
{
  message->asyncRead(lpfnHandleAfterRead, delim);
}

SerialPort::data_type SerialPort::read(size_t size) const
{
  return message->read(size);
}
