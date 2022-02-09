#ifndef __DEV_LIB_MESSAGE_BOOST_TIMERS_H__
#define __DEV_LIB_MESSAGE_BOOST_TIMERS_H__

#include "dev_lib/message/timer_message.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <map>

class BoostTimers
{
public:
  using io_service = boost::asio::io_service;
  using deadline_timer = boost::asio::deadline_timer;
  using RedoTimerCallback = TimerMessage::RedoTimerCallback;
  using HandleTimerCallback = TimerMessage::HandleTimerCallback;
  BoostTimers(io_service& io);
  std::shared_ptr<TimerMessage> addTimer(float delaySeconds, HandleTimerCallback lpfnHandleTimer);

private:
  static long toMilliseconds(float seconds);
  void redo(std::shared_ptr<deadline_timer> timer, HandleTimerCallback lpfnHandleTimer);
  void asyncWait(std::shared_ptr<deadline_timer> timer, HandleTimerCallback lpfnHandleTimer);
  std::map<std::shared_ptr<deadline_timer>, boost::posix_time::time_duration> timers;
  io_service& io;
};

#endif
