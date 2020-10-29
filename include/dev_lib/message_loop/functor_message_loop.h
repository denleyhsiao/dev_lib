#ifndef __DEV_LIB_MESSAGE_LOOP_FUNCTOR_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_LOOP_FUNCTOR_MESSAGE_LOOP_H__

#include "dev_lib/message_loop/message_loop.h"
#include <functional>

class FunctorMessageLoop : public MessageLoop
{
public:
  using HandleCallback = std::function<void()>;
  FunctorMessageLoop(bool isMaster, HandleCallback callback);
  virtual void run() override;

private:
  HandleCallback callback;
};

#endif
