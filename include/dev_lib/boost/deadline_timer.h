#ifndef __DEV_LIB_BOOST_DEADLINE_TIMER_H__
#define __DEV_LIB_BOOST_DEADLINE_TIMER_H__

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <memory>

class DeadlineTimer
{
public:
  typedef std::shared_ptr<boost::asio::deadline_timer> timer_type;
  typedef void (* finish_func_type)(const char* prefix, long seconds);
  DeadlineTimer(boost::asio::io_service& io, long sleepSeconds, finish_func_type callbackFinish);
  virtual ~DeadlineTimer() {}
  void init();
  void wakeUp();
  
protected:
  bool isSameTime() const;
  void async_wait();
  void doPrint(const char* prefix);
  timer_type timer;
  boost::posix_time::time_duration sleepDuration;
  
private:
  virtual void callback(const boost::system::error_code &err) = 0;
  virtual void print(const char* prefix) = 0;
  boost::asio::io_service& io;  
  boost::posix_time::ptime begin;
  boost::posix_time::ptime end;
  finish_func_type callbackFinish;
};

#endif
