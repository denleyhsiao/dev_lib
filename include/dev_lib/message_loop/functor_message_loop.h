#ifndef __DEV_LIB_MESSAGE_LOOP_FUNCTOR_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_LOOP_FUNCTOR_MESSAGE_LOOP_H__

#include "dev_lib/message_loop/message_loop.h"

class FunctorMessageLoop : public MessageLoop
{
public:
  using HandleCallback = std::function<void()>;
  FunctorMessageLoop(HandleCallback callback, bool isMaster = false);
  virtual void add(float delaySeconds, MessageHandlerCallback messageHandler) override;
  virtual void run() override;

private:
  HandleCallback callback;
};

#endif
