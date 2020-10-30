#include "dev_lib/message_loop/functor_message_loop.h"

FunctorMessageLoop::FunctorMessageLoop(HandleCallback callback, bool isMaster /* = false */)
  : MessageLoop(isMaster), callback(callback)
{

}

void FunctorMessageLoop::run()
{
  callback();
}
