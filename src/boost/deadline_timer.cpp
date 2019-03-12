#include "dev_lib/boost/deadline_timer.h"
#include <boost/thread/thread_time.hpp>
#include <boost/bind.hpp>

DeadlineTimer::DeadlineTimer(boost::asio::io_service& io, float sleepSeconds, finish_func_type callbackFinish) 
  : io(io), sleepDuration(boost::posix_time::milliseconds(sleepSeconds * 1000)), callbackFinish(callbackFinish), timer(NULL), stopped(false)
{
}

DeadlineTimer::~DeadlineTimer()
{
  if (timer)
  {
    stopped = true;
    timer->cancel();
  }
}

void DeadlineTimer::init()
{
  timer = timer_type(new boost::asio::deadline_timer(io, sleepDuration));
  stopped = false;
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
    print("recreate");
    init();
  }
}

void DeadlineTimer::async_wait()
{
  timer->async_wait(boost::bind(&DeadlineTimer::callback, this, boost::asio::placeholders::error));  
}

void DeadlineTimer::callback(const boost::system::error_code &err)
{
  if (!stopped && isPaused(err))
  {
    pause();
    async_wait();
  }
  else
  {
    timer.reset();
    stopped = true;
    callbackFinish();
    print("finished");
  }
}

void DeadlineTimer::doPrint(const char* prefix)
{
  std::cout << prefix << (boost::get_system_time() - begin).total_milliseconds()/1000.0 << std::endl;
}
