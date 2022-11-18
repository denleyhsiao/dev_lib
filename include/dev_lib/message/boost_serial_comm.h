#ifndef __DEV_LIB_MESSAGE_BOOST_SERIAL_COMM_H__
#define __DEV_LIB_MESSAGE_BOOST_SERIAL_COMM_H__

#include "dev_lib/message/boost_common_comm.h"
#include <boost/asio/serial_port.hpp>

class BoostSerialComm : public BoostCommonComm<boost::asio::serial_port>
{
public:
  BoostSerialComm(io_service& io) : BoostCommonComm<boost::asio::serial_port>(io) { }

private:
  virtual bool hasInit() const override;
  virtual void doInit() override;
  void setOption(unsigned characterSize);
};

#endif
