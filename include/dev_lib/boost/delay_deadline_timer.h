#ifndef __DEV_LIB_BOOST_DELAY_DEADLINE_TIMER_H__
#define __DEV_LIB_BOOST_DELAY_DEADLINE_TIMER_H__

#include "dev_lib/boost/deadline_timer.h"

class DelayDeadlineTimer : public DeadlineTimer
{
public:
  DelayDeadlineTimer(boost::asio::io_service& io, long sleepSeconds) : DeadlineTimer(io, sleepSeconds) { }
  
private:
  virtual void callback(const boost::system::error_code &err); 
  virtual void print(const char* prefix);
};

#endif
