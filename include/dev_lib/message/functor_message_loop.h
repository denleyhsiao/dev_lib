#ifndef __DEV_LIB_MESSAGE_FUNCTOR_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_FUNCTOR_MESSAGE_LOOP_H__

#include "dev_lib/message/message_loop.h"

class FunctorMessageLoop : public MessageLoop
{
public:
  using HandleCallback = std::function<void()>;
  FunctorMessageLoop(HandleCallback callback, bool isMaster = false);
  virtual std::shared_ptr<TimerMessage> addTimer(float delaySeconds, HandleTimerCallback lpfnHandleTimer) override;
  virtual std::shared_ptr<CommMessage> addSerialComm(const char* port, unsigned int baudrate) override;
  virtual std::shared_ptr<CommMessage> addTCPComm(const char* address, unsigned int port) override;
  virtual void run() override;
  virtual void stop() override;

private:
  HandleCallback callback;
};

#endif
