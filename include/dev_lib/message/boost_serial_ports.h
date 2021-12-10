#ifndef __DEV_LIB_MESSAGE_BOOST_SERIAL_PORTS_H__
#define __DEV_LIB_MESSAGE_BOOST_SERIAL_PORTS_H__

#include <boost/asio/io_service.hpp>
#include <vector>
#include <memory>

class SerialPortMessage;
class BoostSerialPort;
class BoostSerialPorts
{
public:
  using io_service = boost::asio::io_service;
  BoostSerialPorts(io_service& io);
  std::shared_ptr<SerialPortMessage> addSerialPort(const char* port, unsigned int baudrate);

private:
  std::vector<std::shared_ptr<BoostSerialPort> > serialPorts;
  io_service& io;
};

#endif
