#ifndef __DEV_LIB_MESSAGE_BOOST_TIMERS_H__
#define __DEV_LIB_MESSAGE_BOOST_TIMERS_H__

#include "dev_lib/message/timer_message.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <map>
using namespace boost::asio;

class BoostTimers
{
public:
  using RedoMessage = TimerMessage::RedoMessage;
  using HandleMessage = TimerMessage::HandleMessage;
  BoostTimers(io_service& io);
  std::shared_ptr<TimerMessage> addTimer(float delaySeconds, HandleMessage handleMessage);

private:
  static long toMilliseconds(float seconds);
  void redo(std::shared_ptr<deadline_timer> timer, HandleMessage handleMessage);
  void asyncWait(std::shared_ptr<deadline_timer> timer, HandleMessage handleMessage);
  std::map<std::shared_ptr<deadline_timer>, boost::posix_time::time_duration> timers;
  io_service& io;
};

#endif
