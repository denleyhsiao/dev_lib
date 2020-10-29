#include "dev_lib/message_loop/functor_message_loop.h"

FunctorMessageLoop::FunctorMessageLoop(bool isMaster, HandleCallback callback)
  : MessageLoop(isMaster), callback(callback)
{

}

void FunctorMessageLoop::run()
{
  callback();
}
