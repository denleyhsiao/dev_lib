#ifndef __DEV_LIB_DEADLINE_TIMER_H__
#define __DEV_LIB_DEADLINE_TIMER_H__

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class DeadlineTimer
{
public:
  static bool isZero(const boost::posix_time::time_duration& duration);
  DeadlineTimer(float durationSeconds);
  virtual ~DeadlineTimer() {}
  virtual void finishCountDown() {};
  void init();
  void destroy();
  void cancel();
  void countDown();
  void join();

protected:
  static boost::posix_time::time_duration duration(float seconds);
  void reset(float durationSeconds);

private:
  virtual void doCancel() {}
  virtual void doDestroy() {}
  bool hasSyncCancel() const;
  void callback(const boost::system::error_code &ec);
  boost::asio::io_service io;
  boost::asio::io_service::work work;
  boost::posix_time::ptime end;
  boost::posix_time::time_duration powerDuration;
  boost::asio::deadline_timer timer;
  std::shared_ptr<boost::thread> thread;
};

#endif
