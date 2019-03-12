#ifndef __DEV_LIB_BOOST_DEADLINE_TIMER_H__
#define __DEV_LIB_BOOST_DEADLINE_TIMER_H__

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <memory>

class DeadlineTimer
{
public:
  typedef std::shared_ptr<boost::asio::deadline_timer> timer_type;
  typedef std::function<void ()> finish_func_type;
  DeadlineTimer(boost::asio::io_service& io, float sleepSeconds, finish_func_type callbackFinish);
  virtual ~DeadlineTimer();
  void init();
  void wakeUp();
  
protected:
  void doPrint(const char* prefix);
  timer_type timer;
  boost::posix_time::time_duration sleepDuration;
  boost::posix_time::ptime end;
  
private:
  virtual bool isPaused(const boost::system::error_code &err) const = 0;
  virtual void pause() = 0;
  virtual void print(const char* prefix) = 0;
  void callback(const boost::system::error_code &err);
  void async_wait();
  bool stopped;
  boost::asio::io_service& io;  
  boost::posix_time::ptime begin;
  finish_func_type callbackFinish;
};

#endif
