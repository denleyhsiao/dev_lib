#include "dev_lib/message/boost_message_loop.h"
#include "dev_lib/message/timer_message.h"
#include <boost/asio/signal_set.hpp>
#include <boost/system/error_code.hpp>
#include <cassert>

BoostMessageLoop::BoostMessageLoop(std::shared_ptr<Log> log, quit_t quit, bool isMaster /* = false */)
  : MessageLoop(isMaster), timers(io), serialPorts(io, log), quit(quit)
{

}

BoostMessageLoop::~BoostMessageLoop()
{
  stop();
}

std::shared_ptr<TimerMessage> BoostMessageLoop::addTimer(float delaySeconds, HandleMessage handleMessage)
{
  return timers.addTimer(delaySeconds, handleMessage);
}

std::shared_ptr<SerialPortMessage> BoostMessageLoop::addSerialPort(const char* port, unsigned int baudrate)
{
  return serialPorts.addSerialPort(port, baudrate);
}

void BoostMessageLoop::run()
{
  signal_set signal_set(io, SIGINT);
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
