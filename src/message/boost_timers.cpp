#include "dev_lib/message/boost_timers.h"

long BoostTimers::toMilliseconds(float seconds)
{
  return std::ceil(seconds * 1000);
}

BoostTimers::BoostTimers(io_service& io) : io(io)
{

}

std::shared_ptr<TimerMessage> BoostTimers::addTimer(float delaySeconds, HandleMessage handleMessage)
{
  boost::posix_time::time_duration delay = boost::posix_time::milliseconds(toMilliseconds(delaySeconds));
  auto timer = std::make_shared<deadline_timer>(io, delay);
  asyncWait(timer, handleMessage);
  timers[timer] = delay;
  return std::make_shared<TimerMessage>(handleMessage,
    std::bind(&BoostTimers::redo, this, timer, handleMessage),
    [timer]() {
      timer->cancel();
    });
}

void BoostTimers::asyncWait(std::shared_ptr<deadline_timer> timer, HandleMessage handleMessage)
{
  timer->async_wait([timer, handleMessage, this](const boost::system::error_code& ec) {
    if (ec)
      return ;

    handleMessage(std::bind(&BoostTimers::redo, this, timer, handleMessage));
  });
}

void BoostTimers::redo(std::shared_ptr<deadline_timer> timer, HandleMessage handleMessage)
{
  timer->expires_from_now(timers[timer]);
  asyncWait(timer, handleMessage);
}
