#ifndef __DEV_LIB_MESSAGE_BOOST_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_BOOST_MESSAGE_LOOP_H__

#include "dev_lib/message/message_loop.h"
#include "dev_lib/message/boost_timers.h"
#include "dev_lib/message/boost_serial_ports.h"
#include <boost/asio/io_service.hpp>

class Log;
class BoostMessageLoop : public MessageLoop
{
public:
  using quit_t = std::function<void(int number)>;
  BoostMessageLoop(std::shared_ptr<Log> log, quit_t quit, bool isMaster = false);
  ~BoostMessageLoop();
  virtual std::shared_ptr<TimerMessage> addTimer(float delaySeconds, HandleTimerCallback lpfnHandleTimer) override;
  virtual std::shared_ptr<SerialPortMessage> addSerialPort(const char* port, unsigned int baudrate) override;
  virtual void run() override;
  virtual void stop() override;

private:
  void doStop();
  std::shared_ptr<Log> log;
  boost::asio::io_service io;
  BoostTimers timers;
  BoostSerialPorts serialPorts;
  quit_t quit;
};

#endif
