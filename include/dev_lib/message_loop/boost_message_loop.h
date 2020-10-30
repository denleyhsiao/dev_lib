#ifndef __DEV_LIB_MESSAGE_LOOP_BOOST_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_LOOP_BOOST_MESSAGE_LOOP_H__

#include "dev_lib/message_loop/message_loop.h"
#include <boost/asio/io_service.hpp>
#include <functional>
#include <memory>

class BoostMessageLoop : public MessageLoop
{
public:
  using quit_t = std::function<void(int number)>;
  BoostMessageLoop(quit_t quit, bool isMaster = false);
  ~BoostMessageLoop();
  virtual void run() override;
  void doRun();

protected:
  void stop();

private:
  void doStop();
  boost::asio::io_service io;
  quit_t quit;
};

#endif
