#ifndef __DEV_LIB_MESSAGE_MESSAGE_LOOPS_H__
#define __DEV_LIB_MESSAGE_MESSAGE_LOOPS_H__

#include "dev_lib/message/message_loop.h"
#include <memory>

class Log;
class MessageLoops
{
public:
  using RedoMessage = MessageLoop::RedoMessage;
  using HandleMessage = MessageLoop::HandleMessage;
  MessageLoops();
  void init(std::shared_ptr<Log> log, std::shared_ptr<MessageLoop> first, std::shared_ptr<MessageLoop> second);
  bool hasInit() const;
  std::shared_ptr<Message> add(const char* tip, float delaySeconds, HandleMessage handleMessage);
  void run(const char* appName);

private:
  std::shared_ptr<MessageLoop> masterMessageLoop;
  std::shared_ptr<MessageLoop> slaveMessageLoop;
  std::shared_ptr<Log> log;
};

#endif
