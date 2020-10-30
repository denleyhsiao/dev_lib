#include "dev_lib/message_loop/functor_message_loop.h"
#include <cassert>

FunctorMessageLoop::FunctorMessageLoop(HandleCallback callback, bool isMaster /* = false */)
  : MessageLoop(isMaster), callback(callback)
{

}

void FunctorMessageLoop::add(float delaySeconds, HandleMessage handleMessage)
{
  assert(false);
}

void FunctorMessageLoop::run()
{
  callback();
}
