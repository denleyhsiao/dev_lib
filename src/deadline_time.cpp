#include "dev_lib/deadline_time.h"

boost::posix_time::time_duration DeadlineTime::duration(float seconds)
{
  return boost::posix_time::milliseconds(seconds * 1000);
}

DeadlineTime::DeadlineTime(float durationSeconds) : work(io), end(boost::get_system_time()), powerTimer(io, powerDuration), thread(std::shared_ptr<boost::thread>(nullptr))
{
  reset(durationSeconds);
}

void DeadlineTime::init()
{
  thread = std::shared_ptr<boost::thread>(new boost::thread(boost::bind(&boost::asio::io_service::run, &io)));
}

void DeadlineTime::reset(float durationSeconds)
{
  powerDuration = duration(durationSeconds);
}

void DeadlineTime::destroy()
{
  powerTimer.cancel();
  doDestroy();
  if (thread)
    thread->join();
}

void DeadlineTime::cancel()
{
  end = boost::get_system_time();
  powerTimer.cancel();
  doCancel();
}

void DeadlineTime::countDown()
{
  end = boost::get_system_time();
  powerTimer.expires_from_now(powerDuration);
  powerTimer.async_wait(boost::bind(&DeadlineTime::callback, this, boost::asio::placeholders::error));
}

void DeadlineTime::callback(const boost::system::error_code &ec)
{
  if (ec || hasSyncCancel())
    return ;
  finishCountDown();
}

bool DeadlineTime::hasSyncCancel() const
{
  return isZero(boost::get_system_time() - end);
}

bool DeadlineTime::isZero() const
{
  return isZero(powerDuration);
}

bool DeadlineTime::isZero(const boost::posix_time::time_duration& duration)
{
  return (duration.total_milliseconds() == 0);
}
