#include "dev_lib/boost/delay_deadline_timer.h"
#include <boost/thread/thread_time.hpp>
#include "boost/format.hpp"

bool DelayDeadlineTimer::isPaused(const boost::system::error_code &err) const
{
  return (err || isSameTime());
}
  
bool DelayDeadlineTimer::isSameTime() const
{
  return ((boost::get_system_time() - end).total_milliseconds() == 0);
}

void DelayDeadlineTimer::pause()  
{  
  print("received wakeup");
  timer->expires_from_now(sleepDuration);  
}  

void DelayDeadlineTimer::print(const char* prefix)
{
  doPrint((boost::format(" -------------------- Master %s at ") % prefix).str().c_str());
}
