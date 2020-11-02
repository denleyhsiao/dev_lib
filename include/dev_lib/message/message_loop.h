#ifndef __DEV_LIB_MESSAGE_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_MESSAGE_LOOP_H__

#include "dev_lib/message/timer_message.h"
#include <functional>
#include <memory>

class MessageLoop
{
public:
  using RedoMessage = TimerMessage::RedoMessage;
  using HandleMessage = TimerMessage::HandleMessage;
  MessageLoop(bool isMaster = false) : thisIsMaster(isMaster) {}
  bool isMaster() const { return thisIsMaster; }
  virtual ~MessageLoop() {}
  virtual std::shared_ptr<TimerMessage> addTimer(float delaySeconds, HandleMessage handleMessage) = 0;
  virtual void run() = 0;

private:
  bool thisIsMaster;
};

#endif
