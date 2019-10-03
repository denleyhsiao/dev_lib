#ifndef __DEV_LIB_SERIAL_PORT_H__
#define __DEV_LIB_SERIAL_PORT_H__

#include "dev_lib/log.h"
#include <boost/function.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/thread.hpp>

class SerialPort
{
public:
  typedef boost::function<void (LogLevel, const char*)> log_function;
  typedef boost::function<std::string (const char*)> read_function;
  SerialPort(log_function logFunction);
  void init(const char* port, unsigned int baudrate);
  void run();
  void join();
  void cancel();
  void destroy();
  void read(read_function readFunction);

private:
  void setOption(unsigned int baudrate, unsigned characterSize);
  boost::asio::io_service io;
  boost::asio::io_service::work work;
  boost::asio::serial_port impl;
  std::shared_ptr<boost::thread> thread;
  log_function logFunction;
};

#endif
