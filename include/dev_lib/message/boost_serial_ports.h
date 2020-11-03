#ifndef __DEV_LIB_MESSAGE_BOOST_SERIAL_PORTS_H__
#define __DEV_LIB_MESSAGE_BOOST_SERIAL_PORTS_H__

#include <boost/asio/io_service.hpp>
#include <vector>
#include <memory>
using namespace boost::asio;

class Log;
class SerialPortMessage;
class BoostSerialPort;
class BoostSerialPorts
{
public:
  BoostSerialPorts(io_service& io, std::shared_ptr<Log> log);
  std::shared_ptr<SerialPortMessage> addSerialPort(const char* port, unsigned int baudrate);

private:
  std::vector<std::shared_ptr<BoostSerialPort> > serialPorts;
  io_service& io;
  std::shared_ptr<Log> log;
};

#endif
