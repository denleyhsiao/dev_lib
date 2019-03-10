#include "dev_lib/boost/deadline_timer.h"
#include <boost/thread/thread_time.hpp>
#include <boost/bind.hpp>

DeadlineTimer::DeadlineTimer(boost::asio::io_service& io, long sleepSeconds, finish_func_type callbackFinish) 
  : io(io), sleepDuration(boost::posix_time::seconds(sleepSeconds)), callbackFinish(callbackFinish), timer(NULL)
{
}
  
bool DeadlineTimer::isSameTime() const
{
  return ((boost::get_system_time() - end).seconds() == 0);
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
    timer->cancel();
  }
  else
  {
    init();
    print("create ");
  }
}

void DeadlineTimer::async_wait()
{
  timer->async_wait(boost::bind(&DeadlineTimer::callback, this, boost::asio::placeholders::error));  
}

void DeadlineTimer::doPrint(const char* prefix)
{
  callbackFinish(prefix, (boost::get_system_time() - begin).seconds());
}
