#include "dev_lib/message_loop/boost_message_loop.h"
#include <boost/asio/signal_set.hpp>
#include <boost/system/error_code.hpp>
#include <cassert>

long BoostMessageLoop::toMilliseconds(float seconds)
{
  return std::ceil(seconds * 1000);
}

BoostMessageLoop::BoostMessageLoop(quit_t quit, bool isMaster /* = false */)
  : MessageLoop(isMaster), quit(quit)
{

}

BoostMessageLoop::~BoostMessageLoop()
{
  stop();
}

void BoostMessageLoop::add(float delaySeconds, MessageHandlerCallback messageHandler)
{
  boost::posix_time::time_duration delay = boost::posix_time::milliseconds(toMilliseconds(delaySeconds));
  auto timer = std::make_shared<deadline_timer>(io, delay);
  asyncWait(timer, messageHandler);
  timers[timer] = delay;
}

void BoostMessageLoop::asyncWait(std::shared_ptr<deadline_timer> timer, MessageHandlerCallback messageHandler)
{
  timer->async_wait([timer, messageHandler, this](const boost::system::error_code& ec) {
    if (ec)
      return ;

    messageHandler(std::bind(&BoostMessageLoop::redo, this, timer, messageHandler));
  });
}

void BoostMessageLoop::redo(std::shared_ptr<deadline_timer> timer, MessageHandlerCallback messageHandler)
{
  timer->expires_from_now(timers[timer]);
  asyncWait(timer, messageHandler);
}

void BoostMessageLoop::run()
{
  doRun();
}

void BoostMessageLoop::doRun()
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
