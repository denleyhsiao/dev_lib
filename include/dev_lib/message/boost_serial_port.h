#ifndef __DEV_LIB_MESSAGE_BOOST_SERIAL_PORT_H__
#define __DEV_LIB_MESSAGE_BOOST_SERIAL_PORT_H__

#include <boost/asio/streambuf.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/serial_port.hpp>
#include <memory>
#include <functional>
using namespace boost::asio;

class SerialPortMessage;
class BoostSerialPort
{
public:
  typedef std::vector<uint8_t> data_type;
  using HandleAfterReadCallback = std::function<void (const data_type&)>;
  BoostSerialPort(io_service& io);
  ~BoostSerialPort();
  std::shared_ptr<SerialPortMessage> init(const char* port, unsigned int baudrate);

private:
  data_type read(size_t size) const;
  bool hasInit() const;
  void doInit();
  void open();
  void setOption(unsigned characterSize);
  void reInit();
  void cancel();
  void close();
  void destroy();
  void write(const data_type& data);
  void asyncRead(HandleAfterReadCallback lpfnHandleAfterRead, const data_type& delim);
  void doRead(HandleAfterReadCallback lpfnHandleAfterRead, const data_type& delim, boost::system::error_code ec, std::size_t readSize);
  mutable serial_port impl;
  mutable streambuf readContent;
  std::string port;
  unsigned int baudrate;
};

#endif
