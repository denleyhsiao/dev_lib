#ifndef __DEV_LIB_COMM_SERIAL_PORT_H__
#define __DEV_LIB_COMM_SERIAL_PORT_H__

#include "dev_lib/comm/comm.h"
#include <boost/thread.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/serial_port.hpp>
#include <memory>

class SerialPort : public Comm, public std::enable_shared_from_this<SerialPort>
{
public:
  typedef Comm::data_type data_type;
  typedef Comm::cb_read_type cb_read_type;
  static std::shared_ptr<Comm> create(std::shared_ptr<Log> log);
  ~SerialPort();
  virtual bool hasInit() const;
  virtual bool init(const char* serialPort, unsigned int serialBaudrate);
  virtual data_type read(size_t size) const;
  virtual void asyncRead(cb_read_type cbRead, const data_type& delim);

private:
  SerialPort(std::shared_ptr<Log> log);
  virtual void doWrite(const data_type& data);
  void doRead(cb_read_type cbRead, const data_type& delim, boost::system::error_code ec, std::size_t readSize);
  void setOption(unsigned int baudrate, unsigned characterSize);
  void cancel();
  void close();
  boost::asio::io_service io;
  boost::asio::io_service::work work;
  mutable boost::asio::serial_port impl;
  mutable boost::asio::streambuf readContent;
  std::shared_ptr<boost::thread> thread;
};

#endif
