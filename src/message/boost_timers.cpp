#include "dev_lib/message/boost_timers.h"

long BoostTimers::toMilliseconds(float seconds)
{
  return std::ceil(seconds * 1000);
}

BoostTimers::BoostTimers(io_service& io) : io(io)
{

}

std::shared_ptr<TimerMessage> BoostTimers::addTimer(float delaySeconds, HandleTimerCallback lpfnHandleTimer)
{
  boost::posix_time::time_duration delay = boost::posix_time::milliseconds(toMilliseconds(delaySeconds));
  auto timer = std::make_shared<deadline_timer>(io, delay);
  asyncWait(timer, lpfnHandleTimer);
  timers[timer] = delay;
  return std::make_shared<TimerMessage>(lpfnHandleTimer,
    std::bind(&BoostTimers::redo, this, timer, lpfnHandleTimer),
    [timer]() {
      timer->cancel();
    });
}

void BoostTimers::asyncWait(std::shared_ptr<deadline_timer> timer, HandleTimerCallback lpfnHandleTimer)
{
  timer->async_wait([timer, lpfnHandleTimer, this](const boost::system::error_code& ec) {
    if (ec)
      return ;

    lpfnHandleTimer(std::bind(&BoostTimers::redo, this, timer, lpfnHandleTimer));
  });
}

void BoostTimers::redo(std::shared_ptr<deadline_timer> timer, HandleTimerCallback lpfnHandleTimer)
{
  timer->expires_from_now(timers[timer]);
  asyncWait(timer, lpfnHandleTimer);
}
