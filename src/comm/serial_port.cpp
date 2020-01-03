#include "dev_lib/comm/serial_port.h"
#include "dev_lib/dev_helper.h"
#include "dev_lib/log/log.h"
#include <boost/asio/read_until.hpp>
#include <boost/bind.hpp>
#include <cassert>

std::shared_ptr<Comm> SerialPort::create(std::shared_ptr<Log> log)
{
  return std::shared_ptr<Comm>(new SerialPort(log));
}

SerialPort::SerialPort(std::shared_ptr<Log> log) : Comm(log), work(io), impl(io), thread(std::shared_ptr<boost::thread>(nullptr))
{
}

SerialPort::~SerialPort()
{
  close();
  if (thread)
    thread->join();
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
  {
    thread = std::shared_ptr<boost::thread>(new boost::thread(boost::bind(&boost::asio::io_service::run, &io)));
    log->info("Serial port initialized");
  }
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

void SerialPort::asyncRead(size_t size, const data_type& delim, cb_read_type cbRead)
{
  boost::asio::async_read_until(impl, readContent, std::string(delim.begin(), delim.end()),
    boost::bind(&SerialPort::doRead, shared_from_this(), size, delim, cbRead, _1, _2));
}

void SerialPort::doRead(size_t size, const data_type& delim, cb_read_type cbRead, boost::system::error_code ec, std::size_t bytes_transferred)
{
  if (ec)
    log->error(ec.message());
  else
  {
    log->debug(DevHelper::format("Read length: %d", bytes_transferred));
    assert(bytes_transferred >= size);
    boost::asio::streambuf::const_buffers_type content = readContent.data();
    data_type result(boost::asio::buffers_begin(content) + bytes_transferred - size, boost::asio::buffers_begin(content) + bytes_transferred);
    cbRead(result);
  }
  asyncRead(size, delim, cbRead);
}

void SerialPort::cancel()
{
  impl.cancel();
}

void SerialPort::close()
{
  cancel();
  impl.close();
}
