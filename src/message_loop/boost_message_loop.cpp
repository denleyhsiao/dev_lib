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

void BoostMessageLoop::add(float delaySeconds, HandleMessage handleMessage)
{
  boost::posix_time::time_duration delay = boost::posix_time::milliseconds(toMilliseconds(delaySeconds));
  auto timer = std::make_shared<deadline_timer>(io, delay);
  asyncWait(timer, handleMessage);
  timers[timer] = delay;
}

void BoostMessageLoop::asyncWait(std::shared_ptr<deadline_timer> timer, HandleMessage handleMessage)
{
  timer->async_wait([timer, handleMessage, this](const boost::system::error_code& ec) {
    if (ec)
      return ;

    handleMessage(std::bind(&BoostMessageLoop::redo, this, timer, handleMessage));
  });
}

void BoostMessageLoop::redo(std::shared_ptr<deadline_timer> timer, HandleMessage handleMessage)
{
  timer->expires_from_now(timers[timer]);
  asyncWait(timer, handleMessage);
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
