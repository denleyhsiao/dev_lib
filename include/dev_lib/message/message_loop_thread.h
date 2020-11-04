#ifndef __DEV_LIB_MESSAGE_MESSAGE_LOOP_THREAD_H__
#define __DEV_LIB_MESSAGE_MESSAGE_LOOP_THREAD_H__

#include "dev_lib/message/message_loop.h"
#include <boost/thread.hpp>

class MessageLoopThread : public MessageLoop
{
public:
  MessageLoopThread(std::shared_ptr<MessageLoop> messageLoop);
  ~MessageLoopThread();
  virtual std::shared_ptr<TimerMessage> addTimer(float delaySeconds, HandleTimerCallback lpfnHandleTimer) override;
  virtual std::shared_ptr<SerialPortMessage> addSerialPort(const char* port, unsigned int baudrate) override;
  virtual void run() override;
  virtual void stop() override;

private:
  void join();
  std::shared_ptr<MessageLoop> messageLoop;
  std::shared_ptr<boost::thread> thread;
};

#endif
