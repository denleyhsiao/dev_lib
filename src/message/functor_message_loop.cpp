#include "dev_lib/message/functor_message_loop.h"
#include <cassert>

FunctorMessageLoop::FunctorMessageLoop(HandleCallback callback, bool isMaster /* = false */)
  : MessageLoop(isMaster), callback(callback)
{

}

std::shared_ptr<TimerMessage> FunctorMessageLoop::addTimer(float delaySeconds, HandleTimerCallback lpfnHandleTimer)
{
  assert(false);
  return nullptr;
}

std::shared_ptr<CommMessage> FunctorMessageLoop::addSerialComm(const char* port, unsigned int baudrate)
{
  assert(false);
  return nullptr;
}

std::shared_ptr<CommMessage> FunctorMessageLoop::addTCPComm(const char* address, unsigned int port)
{
  assert(false);
  return nullptr;
}

void FunctorMessageLoop::run()
{
  callback();
}

void FunctorMessageLoop::stop()
{

}
