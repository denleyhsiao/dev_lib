#include "dev_lib/message/boost_serial_port.h"
#include "dev_lib/message/serial_port_message.h"
#include "dev_lib/log/log_harness.h"
#include "dev_lib/dev_helper.h"
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>

BoostSerialPort::BoostSerialPort(io_service& io) : impl(io)
{

}

BoostSerialPort::~BoostSerialPort()
{
  destroy();
}

bool BoostSerialPort::hasInit() const
{
  return impl.is_open();
}

std::shared_ptr<SerialPortMessage> BoostSerialPort::init(const char* port, unsigned int baudrate)
{
  this->port = port;
  this->baudrate = baudrate;
  doInit();
  return std::make_shared<SerialPortMessage>(
    std::bind(&BoostSerialPort::hasInit, this),
    std::bind(&BoostSerialPort::reInit, this),
    std::bind(&BoostSerialPort::write, this, std::placeholders::_1),
    std::bind(&BoostSerialPort::asyncRead, this, std::placeholders::_1, std::placeholders::_2),
    std::bind(&BoostSerialPort::read, this, std::placeholders::_1));
}

void BoostSerialPort::doInit()
{
  open();
  if (hasInit())
    LOG(INFO) << "Serial port initialized: " << port << "(" << baudrate << ")";
  else
    LOG(ERROR) << "Serial port can't open: " << port << "(" << baudrate << ")";
}

void BoostSerialPort::open()
{
  assert(!hasInit());

  boost::system::error_code ec;
  impl.open(port.c_str(), ec);
  if (ec)
    LOG(ERROR) << ec.message();
  else
    setOption(8);
}

void BoostSerialPort::setOption(unsigned characterSize)
{
  impl.set_option(serial_port::baud_rate(baudrate));
  impl.set_option(serial_port::flow_control(serial_port::flow_control::none));
  impl.set_option(serial_port::parity(serial_port::parity::none));
  impl.set_option(serial_port::stop_bits(serial_port::stop_bits::one));
  impl.set_option(serial_port::character_size(characterSize));
}

void BoostSerialPort::reInit()
{
  destroy();
  doInit();
}

void BoostSerialPort::destroy()
{
  if (hasInit())
    close();
}

void BoostSerialPort::close()
{
  cancel();
  impl.close();
}

void BoostSerialPort::cancel()
{
  impl.cancel();
}

void BoostSerialPort::write(const data_type& data)
{
  boost::system::error_code ec;
  impl.write_some(boost::asio::buffer(data), ec);
  if (ec)
    LOG(ERROR) << ec.message();
}

BoostSerialPort::data_type BoostSerialPort::read(size_t size) const
{
  boost::system::error_code ec;
  std::size_t readSize = 0;
  do
  {
    readSize += boost::asio::read(impl, readContent, boost::asio::transfer_exactly(1), ec);
    if (ec)
      break;
  } while(readSize < size);

  data_type result = data_type();
  if(ec)
    LOG(ERROR) << ec.message();
  else
  {
    boost::asio::streambuf::const_buffers_type content = readContent.data();
    result = data_type(boost::asio::buffers_begin(content), boost::asio::buffers_begin(content) + size);
    readContent.consume(readSize);
  }

  return result;
}

void BoostSerialPort::asyncRead(HandleAfterReadCallback lpfnHandleAfterRead, const data_type& delim)
{
  boost::asio::async_read_until(impl, readContent, std::string(delim.begin(), delim.end()),
    std::bind(&BoostSerialPort::doRead, this, lpfnHandleAfterRead, delim, std::placeholders::_1, std::placeholders::_2));
}

void BoostSerialPort::doRead(HandleAfterReadCallback lpfnHandleAfterRead, const data_type& delim, boost::system::error_code ec, std::size_t readSize)
{
  if (ec)
    LOG(ERROR) << ec.message();
  else
  {
    boost::asio::streambuf::const_buffers_type content = readContent.data();
    data_type result(boost::asio::buffers_begin(content), boost::asio::buffers_begin(content) + readSize);
    lpfnHandleAfterRead(result);
    readContent.consume(readSize);
  }
  asyncRead(lpfnHandleAfterRead, delim);
}
