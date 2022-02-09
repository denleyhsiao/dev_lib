#include "dev_lib/message/boost_message_loop.h"
#include "dev_lib/message/timer_message.h"
#include "dev_lib/message/boost_serial_comm.h"
#include "dev_lib/message/boost_tcp_comm.h"
#include <boost/asio/signal_set.hpp>
#include <boost/system/error_code.hpp>
#include <cassert>

BoostMessageLoop::BoostMessageLoop(quit_t quit, bool isMaster /* = false */)
  : MessageLoop(isMaster), timers(io), quit(quit)
{

}

BoostMessageLoop::~BoostMessageLoop()
{
  stop();
}

std::shared_ptr<TimerMessage> BoostMessageLoop::addTimer(float delaySeconds, HandleTimerCallback lpfnHandleTimer)
{
  return timers.addTimer(delaySeconds, lpfnHandleTimer);
}

std::shared_ptr<CommMessage> BoostMessageLoop::addSerialComm(const char* port, unsigned int baudrate)
{
  auto serialComm = std::make_shared<BoostSerialComm>(io);
  serialComms.push_back(serialComm);
  return serialComm->init(port, baudrate);
}

std::shared_ptr<CommMessage> BoostMessageLoop::addTCPComm(const char* address, unsigned int port)
{
  auto tcpComm = std::make_shared<BoostTCPComm>(io);
  tcpComms.push_back(tcpComm);
  return tcpComm->init(address, port);
}

void BoostMessageLoop::run()
{
  boost::asio::signal_set signal_set(io, SIGINT);
  signal_set.async_wait([this](const boost::system::error_code& ec, int number) {
    this->doStop();
    this->quit(number);
  });
  io.run();
}

void BoostMessageLoop::stop()
{
  if (!io.stopped())
    doStop();
}

void BoostMessageLoop::doStop()
{
  io.stop();
}
