#include "dev_lib/message/message_loop_thread.h"

MessageLoopThread::MessageLoopThread(std::shared_ptr<MessageLoop> messageLoop)
  : MessageLoop(messageLoop->isMaster()), messageLoop(messageLoop), thread(nullptr)
{

}

MessageLoopThread::~MessageLoopThread()
{
  messageLoop->stop();
  join();
}

std::shared_ptr<TimerMessage> MessageLoopThread::addTimer(float delaySeconds, HandleTimerCallback lpfnHandleTimer)
{
  return messageLoop->addTimer(delaySeconds, lpfnHandleTimer);
}

std::shared_ptr<CommMessage> MessageLoopThread::addSerialComm(const char* port, unsigned int baudrate)
{
  return messageLoop->addSerialComm(port, baudrate);
}

std::shared_ptr<CommMessage> MessageLoopThread::addTCPComm(const char* address, unsigned int port)
{
  return messageLoop->addTCPComm(address, port);
}

void MessageLoopThread::run()
{
  thread = std::make_shared<boost::thread>(&MessageLoop::run, messageLoop);
  if (isMaster())
    join();
}

void MessageLoopThread::stop()
{
  messageLoop->stop();
}

void MessageLoopThread::join()
{
  if (thread && thread->joinable())
    thread->join();
}
