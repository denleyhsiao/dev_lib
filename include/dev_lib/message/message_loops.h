#ifndef __DEV_LIB_MESSAGE_MESSAGE_LOOPS_H__
#define __DEV_LIB_MESSAGE_MESSAGE_LOOPS_H__

#include "dev_lib/message/message_loop.h"
#include <map>
#include <memory>

class MessageLoops
{
public:
  using RedoTimerCallback = MessageLoop::RedoTimerCallback;
  using HandleTimerCallback = MessageLoop::HandleTimerCallback;
  MessageLoops();
  void init(std::shared_ptr<MessageLoop> first, std::shared_ptr<MessageLoop> second);
  bool hasInit() const;
  std::shared_ptr<TimerMessage> addTimer(const char* tip, float delaySeconds, HandleTimerCallback lpfnHandleTimer);
  std::shared_ptr<CommMessage> addSerialComm(const char* port, unsigned int baudrate);
  std::shared_ptr<CommMessage> addTCPComm(const char* address, unsigned int port);
  void run(const char* appName);

private:
  bool hasOnlyOne() const;
  void set(std::shared_ptr<MessageLoop> value);
  std::map<bool, std::shared_ptr<MessageLoop> > messageLoops;
  bool isAddOnMaster;
};

#endif
