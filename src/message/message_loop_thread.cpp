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

std::shared_ptr<TimerMessage> MessageLoopThread::addTimer(float delaySeconds, HandleMessage handleMessage)
{
  return messageLoop->addTimer(delaySeconds, handleMessage);
}

std::shared_ptr<SerialPortMessage> MessageLoopThread::addSerialPort(const char* port, unsigned int baudrate)
{
  return messageLoop->addSerialPort(port, baudrate);
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
