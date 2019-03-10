#include "dev_lib/boost/delay_deadline_timer.h"
#include "boost/format.hpp"

void DelayDeadlineTimer::callback(const boost::system::error_code &err)  
{  
  if (err || isSameTime())
  {
    print("received wakeup");
    timer->expires_from_now(sleepDuration);  
    async_wait();
  }
  else
  {
    timer.reset();
    print("finished");
  }
}  

void DelayDeadlineTimer::print(const char* prefix)
{
  doPrint((boost::format(" -------------------- Master %s at ") % prefix).str().c_str());
}
