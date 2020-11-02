#include "dev_lib/message/boost_message_loop.h"
#include "dev_lib/message/timer_message.h"
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

std::shared_ptr<TimerMessage> BoostMessageLoop::add(float delaySeconds, HandleMessage handleMessage)
{
  boost::posix_time::time_duration delay = boost::posix_time::milliseconds(toMilliseconds(delaySeconds));
  auto timer = std::make_shared<deadline_timer>(io, delay);
  asyncWait(timer, handleMessage);
  timers[timer] = delay;
  return std::make_shared<TimerMessage>(handleMessage,
    std::bind(&BoostMessageLoop::redo, this, timer, handleMessage),
    [timer]() {
      timer->cancel();
    });
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
