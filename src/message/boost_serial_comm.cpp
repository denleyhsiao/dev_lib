#include "dev_lib/message/boost_serial_comm.h"

bool BoostSerialComm::hasInit() const
{
  return impl.is_open();
}

void BoostSerialComm::doInit()
{
  assert(!hasInit());

  boost::system::error_code ec;
  impl.open(argv1.c_str(), ec);
  if (ec)
    LOG(ERROR) << ec.message();
  else
    setOption(8);
}

void BoostSerialComm::setOption(unsigned characterSize)
{
  using serial_port = boost::asio::serial_port;
  impl.set_option(serial_port::baud_rate(argv2));
  impl.set_option(serial_port::flow_control(serial_port::flow_control::none));
  impl.set_option(serial_port::parity(serial_port::parity::none));
  impl.set_option(serial_port::stop_bits(serial_port::stop_bits::one));
  impl.set_option(serial_port::character_size(characterSize));
}
