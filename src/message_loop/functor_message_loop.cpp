#include "dev_lib/message_loop/functor_message_loop.h"
#include <cassert>

FunctorMessageLoop::FunctorMessageLoop(HandleCallback callback, bool isMaster /* = false */)
  : MessageLoop(isMaster), callback(callback)
{

}

std::tuple<FunctorMessageLoop::CancelMessage, FunctorMessageLoop::RedoMessage>
  FunctorMessageLoop::add(float delaySeconds, HandleMessage handleMessage)
{
  assert(false);
  return std::make_tuple(nullptr, nullptr);
}

void FunctorMessageLoop::run()
{
  callback();
}
