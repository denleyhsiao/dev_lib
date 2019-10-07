#ifndef __DEV_LIB_SERIAL_PORT_H__
#define __DEV_LIB_SERIAL_PORT_H__

#include "dev_lib/log.h"
#include <boost/asio/serial_port.hpp>
#include <boost/thread.hpp>
#include <functional>

class SerialPort
{
public:
  typedef std::function<void (LogLevel, const char*)> log_cb_function;
  typedef std::function<void (const std::string&)> read_cb_function;
  SerialPort(log_cb_function logCallback);
  void init(const char* port, unsigned int baudrate);
  void run(read_cb_function readCallback, const char* prevfix, const char* postfix);
  void join();
  void cancel();
  void destroy();

private:
  void read(read_cb_function readCallback, const char* prevfix, const char* postfix);
  void setOption(unsigned int baudrate, unsigned characterSize);
  boost::asio::io_service io;
  boost::asio::io_service::work work;
  boost::asio::serial_port impl;
  std::shared_ptr<boost::thread> thread;
  log_cb_function logCallback;
};

#endif
