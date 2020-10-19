#include "dev_lib/deadline_timer.h"
#include "dev_lib/boost_helper.h"

boost::posix_time::time_duration DeadlineTimer::duration(float seconds)
{
  return BoostHelper::getTimeDuration(seconds);
}

DeadlineTimer::DeadlineTimer(float durationSeconds) : work(io), end(boost::get_system_time()), timer(io, powerDuration), thread(std::shared_ptr<boost::thread>(nullptr))
{
  reset(durationSeconds);
}

void DeadlineTimer::init()
{
  thread = std::make_shared<boost::thread>(boost::bind(&boost::asio::io_service::run, &io));
}

void DeadlineTimer::join()
{
  if (thread)
    thread->join();
}

void DeadlineTimer::reset(float durationSeconds)
{
  powerDuration = duration(durationSeconds);
}

void DeadlineTimer::destroy()
{
  timer.cancel();
  doDestroy();
  join();
}

void DeadlineTimer::cancel()
{
  end = boost::get_system_time();
  timer.cancel();
  doCancel();
}

void DeadlineTimer::countDown()
{
  end = boost::get_system_time();
  timer.expires_from_now(powerDuration);
  timer.async_wait(boost::bind(&DeadlineTimer::callback, this, boost::asio::placeholders::error));
}

void DeadlineTimer::callback(const boost::system::error_code &ec)
{
  if (ec || hasSyncCancel())
    return ;
  finishCountDown();
}

bool DeadlineTimer::hasSyncCancel() const
{
  return isZero(boost::get_system_time() - end);
}

bool DeadlineTimer::isZero(const boost::posix_time::time_duration& duration)
{
  return (duration.total_milliseconds() == 0);
}
