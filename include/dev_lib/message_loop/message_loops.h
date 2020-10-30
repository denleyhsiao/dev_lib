#ifndef __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOPS_H__
#define __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOPS_H__

#include "dev_lib/message_loop/message_loop.h"
#include <memory>

class Log;
class MessageLoops
{
public:
  using CancelMessage = MessageLoop::CancelMessage;
  using RedoMessage = MessageLoop::RedoMessage;
  using HandleMessage = MessageLoop::HandleMessage;
  MessageLoops();
  void init(std::shared_ptr<MessageLoop> messageLoop, std::shared_ptr<Log> log);
  bool hasInit() const;
  std::tuple<CancelMessage, RedoMessage> add(const char* tip, float delaySeconds, HandleMessage handleMessage);
  void run(const char* appName);

private:
  void quit(int number) const;
  std::shared_ptr<MessageLoop> masterMessageLoop;
  std::shared_ptr<MessageLoop> slaveMessageLoop;
  std::shared_ptr<Log> log;
};

#endif
