#ifndef __DEV_LIB_COMM_SERIAL_PORT_H__
#define __DEV_LIB_COMM_SERIAL_PORT_H__

#include "dev_lib/comm/comm.h"
#include <boost/asio/serial_port.hpp>
#include <memory>

class SerialPort : public Comm
{
public:
  typedef Comm::data_type data_type;
  static std::shared_ptr<Comm> create(std::shared_ptr<Log> log);
  virtual bool hasInit() const;
  virtual bool init(const char* serialPort, unsigned int serialBaudrate);
  virtual data_type read(size_t size) const;

private:
  SerialPort(std::shared_ptr<Log> log);
  virtual void doWrite(const data_type& data);
  void setOption(unsigned int baudrate, unsigned characterSize);
  boost::asio::io_service io;
  boost::asio::io_service::work work;
  boost::asio::serial_port impl;
};

#endif
