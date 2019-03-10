#include "dev_lib/boost/deadline_timer.h"
#include <boost/thread/thread_time.hpp>
#include <boost/bind.hpp>
#include <iostream>

DeadlineTimer::DeadlineTimer(boost::asio::io_service& io, long sleepSeconds) 
  : io(io), sleepDuration(boost::posix_time::seconds(sleepSeconds)), timer(NULL)
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
  std::cout << prefix << (boost::get_system_time() - begin).seconds() << std::endl;
}
