#ifndef __DEV_LIB_DEADLINE_TIME_H__
#define __DEV_LIB_DEADLINE_TIME_H__

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class DeadlineTime
{
public:
  static bool isZero(const boost::posix_time::time_duration& duration);
  DeadlineTime(boost::asio::io_service& io, float durationSeconds);
  virtual ~DeadlineTime() {}
  void init();
  void destroy();
  void cancel();
  void countDown();

protected:
  static boost::posix_time::time_duration duration(float seconds);
  bool isZero() const;
  void reset(float durationSeconds);

private:
  virtual void doDestroy() = 0;
  virtual void finishCountDown() = 0;
  bool hasSyncCancel() const;
  void callback(const boost::system::error_code &ec);
  boost::asio::io_service& io;
  boost::posix_time::ptime end;
  boost::posix_time::time_duration powerDuration;
  boost::asio::deadline_timer powerTimer;
  std::shared_ptr<boost::thread> thread;
};

#endif
