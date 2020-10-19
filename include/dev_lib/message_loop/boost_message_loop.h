#ifndef __DEV_LIB_MESSAGE_LOOP_BOOST_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_LOOP_BOOST_MESSAGE_LOOP_H__

#include "dev_lib/message_loop/message_loop.h"
#include <boost/asio/io_service.hpp>

class BoostMessageLoop : public MessageLoop
{
public:
  BoostMessageLoop(std::shared_ptr<Log> log);
  ~BoostMessageLoop();
  virtual void run(quit_t quit) override;
  void doRun(quit_t quit);

protected:
  void stop();
  std::shared_ptr<Log> log;

private:
  void doStop();
  boost::asio::io_service io;
};

#endif
