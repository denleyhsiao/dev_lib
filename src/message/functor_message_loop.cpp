#include "dev_lib/message/functor_message_loop.h"
#include <cassert>

FunctorMessageLoop::FunctorMessageLoop(HandleCallback callback, bool isMaster /* = false */)
  : MessageLoop(isMaster), callback(callback)
{

}

std::shared_ptr<TimerMessage> FunctorMessageLoop::addTimer(float delaySeconds, HandleMessage handleMessage)
{
  assert(false);
  return nullptr;
}

void FunctorMessageLoop::run()
{
  callback();
}
