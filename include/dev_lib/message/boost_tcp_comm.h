#ifndef __DEV_LIB_MESSAGE_BOOST_TCP_COMM_H__
#define __DEV_LIB_MESSAGE_BOOST_TCP_COMM_H__

#include "dev_lib/message/boost_common_comm.h"
#include <boost/asio/ip/tcp.hpp>

class BoostTCPComm : public BoostCommonComm<boost::asio::ip::tcp::socket>
{
public:
  BoostTCPComm(io_service& io) : BoostCommonComm<boost::asio::ip::tcp::socket>(io) { }

private:
  virtual bool hasInit() const override;
  virtual void doInit() override;
};

#endif
