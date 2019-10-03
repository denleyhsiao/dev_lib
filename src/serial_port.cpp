#include "dev_lib/serial_port.h"

SerialPort::SerialPort(log_function logFunction) : work(io), impl(io), logFunction(logFunction)
{

}

void SerialPort::init(const char* port, unsigned int baudrate)
{
  boost::system::error_code ec;
  impl.open(port, ec);
  if (ec)
  {
    logFunction(LOG_ERROR, ec.message().c_str());
    return ;
  }
  setOption(baudrate, 8);
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

void SerialPort::run()
{
  thread = std::shared_ptr<boost::thread>(new boost::thread(boost::bind(&boost::asio::io_service::run, &io)));
}

void SerialPort::join()
{
  if (thread)
    thread->join();
}

void SerialPort::cancel()
{
  impl.cancel();
}

void SerialPort::destroy()
{
  cancel();
  join();
}

void SerialPort::read(read_function readFunction)
{
  // impl.async_read_some();
}
