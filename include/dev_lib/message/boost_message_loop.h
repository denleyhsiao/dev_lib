#ifndef __DEV_LIB_MESSAGE_BOOST_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_BOOST_MESSAGE_LOOP_H__

#include "dev_lib/message/message_loop.h"
#include "dev_lib/message/boost_timers.h"
#include <boost/asio/io_service.hpp>
#include <vector>

class BoostSerialComm;
class BoostTCPComm;
class BoostMessageLoop : public MessageLoop
{
public:
  using quit_t = std::function<void(int number)>;
  BoostMessageLoop(quit_t quit, bool isMaster = false);
  ~BoostMessageLoop();
  virtual std::shared_ptr<TimerMessage> addTimer(float delaySeconds, HandleTimerCallback lpfnHandleTimer) override;
  virtual std::shared_ptr<CommMessage> addSerialComm(const char* port, unsigned int baudrate) override;
  virtual std::shared_ptr<CommMessage> addTCPComm(const char* address, unsigned int port) override;
  virtual void run() override;
  virtual void stop() override;

private:
  void doStop();
  boost::asio::io_service io;
  BoostTimers timers;
  std::vector<std::shared_ptr<BoostSerialComm> > serialComms;
  std::vector<std::shared_ptr<BoostTCPComm> > tcpComms;
  quit_t quit;
};

#endif
