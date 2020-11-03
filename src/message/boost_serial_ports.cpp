#include "dev_lib/message/boost_serial_ports.h"
#include "dev_lib/message/boost_serial_port.h"

BoostSerialPorts::BoostSerialPorts(io_service& io, std::shared_ptr<Log> log) : io(io), log(log)
{
}

std::shared_ptr<SerialPortMessage> BoostSerialPorts::addSerialPort(const char* port, unsigned int baudrate)
{
  auto serialPort = std::make_shared<BoostSerialPort>(io, log);
  serialPorts.push_back(serialPort);
  return serialPort->init(port, baudrate);
}
