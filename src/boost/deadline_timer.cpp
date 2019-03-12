#include "dev_lib/boost/deadline_timer.h"
#include <boost/thread/thread_time.hpp>
#include <boost/bind.hpp>

DeadlineTimer::DeadlineTimer(boost::asio::io_service& io, float sleepSeconds, finish_func_type callbackFinish) 
  : io(io), sleepDuration(boost::posix_time::milliseconds(sleepSeconds * 1000)), callbackFinish(callbackFinish), timer(NULL)
{
}
  
bool DeadlineTimer::isSameTime() const
{
  return ((boost::get_system_time() - end).total_milliseconds() == 0);
}

void DeadlineTimer::init()
{
  timer = timer_type(new boost::asio::deadline_timer(io, sleepDuration));
  begin = end = boost::get_system_time();
  async_wait();
}

void DeadlineTimer::wakeUp()
{
  if (timer)
  {
    end = boost::get_system_time();
    cancel();
  }
  else
  {
    init();
  }
}

void DeadlineTimer::cancel()
{
  if (timer)
    timer->cancel();
}

void DeadlineTimer::async_wait()
{
  timer->async_wait(boost::bind(&DeadlineTimer::callback, this, boost::asio::placeholders::error));  
}

void DeadlineTimer::doPrint(const char* prefix)
{
  callbackFinish(prefix, (boost::get_system_time() - begin).total_milliseconds()/1000.0);
}
