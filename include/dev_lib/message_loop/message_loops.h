#ifndef __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOPS_H__
#define __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOPS_H__

#include <memory>

class Log;
class MessageLoop;
class MessageLoops
{
public:
  MessageLoops();
  void init(std::shared_ptr<MessageLoop> messageLoop, std::shared_ptr<Log> log);
  bool hasInit() const;
  void run(const char* appName);

private:
  void quit(int number) const;
  std::shared_ptr<MessageLoop> masterMessageLoop;
  std::shared_ptr<MessageLoop> slaveMessageLoop;
  std::shared_ptr<Log> log;
};

#endif
