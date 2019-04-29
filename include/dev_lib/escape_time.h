#ifndef __DEV_LIB_ESCAPE_TIME_H__
#define __DEV_LIB_ESCAPE_TIME_H__

#include <boost/thread/thread_time.hpp>
#include <iostream>

class EscapeTime
{
public:
  static boost::posix_time::ptime current();
  EscapeTime();
  EscapeTime(std::ostream& os);
  ~EscapeTime();
  void print() const;
  long total_milliseconds() const;

private:
  std::ostream& os;
  boost::posix_time::ptime begin;
};

#endif
