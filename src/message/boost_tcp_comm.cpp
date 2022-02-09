#include "dev_lib/message/boost_tcp_comm.h"

bool BoostTCPComm::hasInit() const
{
  return impl.is_open();
}

void BoostTCPComm::doInit()
{
  assert(!hasInit());
  impl.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(argv1), argv2));
}
