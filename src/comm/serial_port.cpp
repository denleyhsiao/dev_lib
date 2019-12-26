#include "dev_lib/comm/serial_port.h"
#include "dev_lib/dev_helper.h"
#include "dev_lib/boost_helper.h"
#include "dev_lib/log/log.h"

std::shared_ptr<Comm> SerialPort::create(std::shared_ptr<Log> log)
{
  return std::shared_ptr<Comm>(new SerialPort(log));
}

SerialPort::SerialPort(std::shared_ptr<Log> log) : Comm(log), work(io), impl(io)
{
}

bool SerialPort::hasInit() const
{
  return impl.is_open();
}

bool SerialPort::init(const char* serialPort, unsigned int serialBaudrate)
{
  bool result = (system(DevHelper::format("sudo chmod 666 %s", serialPort).c_str()) == 0);
  if (!result)
  {
    log->error(DevHelper::format("Unable to sudo chmod 666 %s", serialPort));
    return result;
  }

  boost::system::error_code ec;
  impl.open(serialPort, ec);
  if (ec)
  {
    log->error(ec.message());
    return false;
  }
  setOption(serialBaudrate, 8);

  result = hasInit();
  if (result)
    log->info("Serial port initialized");
  else
    log->error("Serial port can't open");
  return result;
}

void SerialPort::setOption(unsigned int baudrate, unsigned characterSize)
{
  using namespace boost::asio;
  impl.set_option(serial_port::baud_rate(baudrate));
  impl.set_option(serial_port::flow_control(serial_port::flow_control::none));
  impl.set_option(serial_port::parity(serial_port::parity::none));
  impl.set_option(serial_port::stop_bits(serial_port::stop_bits::one));
  impl.set_option(serial_port::character_size(characterSize));
}

void SerialPort::doWrite(const data_type& data)
{
  boost::system::error_code ec;
  impl.write_some(boost::asio::buffer(data), ec);
  if (ec)
    log->error(ec.message());
}

SerialPort::data_type SerialPort::read(size_t size) const
{
  return data_type();
}

SerialPort::data_type SerialPort::read(size_t size, bool needSleep) const
{
  if (needSleep)
    BoostHelper::sleep(0.003);
  return read(size);
}
