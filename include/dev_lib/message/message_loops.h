#ifndef __DEV_LIB_MESSAGE_MESSAGE_LOOPS_H__
#define __DEV_LIB_MESSAGE_MESSAGE_LOOPS_H__

#include "dev_lib/message/message_loop.h"
#include <map>
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
  std::shared_ptr<TimerMessage> addTimer(const char* tip, float delaySeconds, HandleMessage handleMessage);
  void run(const char* appName);

private:
  bool hasOnlyOne() const;
  void set(std::shared_ptr<MessageLoop> value);
  std::map<bool, std::shared_ptr<MessageLoop> > messageLoops;
  std::shared_ptr<Log> log;
  bool isAddOnMaster;
};

#endif
