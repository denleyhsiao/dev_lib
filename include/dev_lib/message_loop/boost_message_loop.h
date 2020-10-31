#ifndef __DEV_LIB_MESSAGE_LOOP_BOOST_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_LOOP_BOOST_MESSAGE_LOOP_H__

#include "dev_lib/message_loop/message_loop.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <map>
using namespace boost::asio;

class BoostMessageLoop : public MessageLoop
{
public:
  using quit_t = std::function<void(int number)>;
  BoostMessageLoop(quit_t quit, bool isMaster = false);
  ~BoostMessageLoop();
  virtual std::shared_ptr<Message> add(float delaySeconds, HandleMessage handleMessage) override;
  virtual void run() override;
  void doRun();

protected:
  void stop();

private:
  void redo(std::shared_ptr<deadline_timer> timer, HandleMessage handleMessage);
  void asyncWait(std::shared_ptr<deadline_timer> timer, HandleMessage handleMessage);
  void doStop();
  static long toMilliseconds(float seconds);
  io_service io;
  std::map<std::shared_ptr<deadline_timer>, boost::posix_time::time_duration> timers;
  quit_t quit;
};

#endif
