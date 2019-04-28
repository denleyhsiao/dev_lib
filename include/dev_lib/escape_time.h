#ifndef __DEV_LIB_ESCAPE_TIME_H__
#define __DEV_LIB_ESCAPE_TIME_H__

#include <boost/thread/thread_time.hpp>

class EscapeTime
{
public:
  EscapeTime();
  ~EscapeTime();

private:
  boost::posix_time::ptime begin;
};

#endif
