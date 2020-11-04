#ifndef __DEV_LIB_MESSAGE_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_MESSAGE_LOOP_H__

#include "dev_lib/message/timer_message.h"
#include <functional>
#include <memory>

class SerialPortMessage;
class MessageLoop
{
public:
  using RedoTimerCallback = TimerMessage::RedoTimerCallback;
  using HandleTimerCallback = TimerMessage::HandleTimerCallback;
  MessageLoop(bool isMaster = false) : thisIsMaster(isMaster) {}
  bool isMaster() const { return thisIsMaster; }
  virtual ~MessageLoop() {}
  virtual std::shared_ptr<TimerMessage> addTimer(float delaySeconds, HandleTimerCallback lpfnHandleTimer) = 0;
  virtual std::shared_ptr<SerialPortMessage> addSerialPort(const char* port, unsigned int baudrate) = 0;
  virtual void run() = 0;
  virtual void stop() = 0;

private:
  bool thisIsMaster;
};

#endif
