#ifndef __DEVLIB_LIB_COMM_SERIAL_PORT_H__
#define __DEVLIB_LIB_COMM_SERIAL_PORT_H__

#include "dev_lib/comm/comm.h"
#include <memory>

class SerialPortMessage;
class SerialPort : public Comm
{
public:
  typedef Comm::data_type data_type;
  SerialPort();
  virtual void reopen();
  virtual bool hasInit() const;
  virtual bool init(const char* port, unsigned int baudrate, HandleInitCallback lpfnHandleInit);
  virtual data_type read(size_t size) const;
  virtual void asyncRead(HandleAfterReadCallback lpfnHandleAfterRead, const data_type& delim);

private:
  virtual void doWrite(const data_type& data);
  std::shared_ptr<SerialPortMessage> message;
};

#endif
