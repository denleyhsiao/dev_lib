#include "dev_lib/message/message_loops.h"
#include "dev_lib/message/message_loop_thread.h"
#include "dev_lib/log/log.h"
#include "dev_lib/dev_helper.h"
#include <cassert>

MessageLoops::MessageLoops() : log(nullptr), isAddOnMaster(false)
{
}

void MessageLoops::init(std::shared_ptr<Log> log, std::shared_ptr<MessageLoop> first, std::shared_ptr<MessageLoop> second)
{
  this->log = log;
  set(first);
  set(second);
  if (hasOnlyOne())
    isAddOnMaster = messageLoops.begin()->first;
}

void MessageLoops::set(std::shared_ptr<MessageLoop> value)
{
  if (value)
  {
    bool isMaster = value->isMaster();
    messageLoops[isMaster] = (isMaster ? value : std::make_shared<MessageLoopThread>(value));
  }
}

bool MessageLoops::hasInit() const
{
  return !messageLoops.empty();
}

bool MessageLoops::hasOnlyOne() const
{
  return (messageLoops.size() == 1);
}

std::shared_ptr<TimerMessage> MessageLoops::addTimer(const char* tip, float delaySeconds, HandleTimerCallback lpfnHandleTimer)
{
  log->info(DevHelper::format("Add message of %s: %.3f second(s)", tip, delaySeconds));
  return messageLoops[isAddOnMaster]->addTimer(delaySeconds, lpfnHandleTimer);
}

std::shared_ptr<SerialPortMessage> MessageLoops::addSerialPort(const char* port, unsigned int baudrate)
{
  return messageLoops[isAddOnMaster]->addSerialPort(port, baudrate);
}

void MessageLoops::run(const char* appName)
{
  assert(hasInit());
  log->info(DevHelper::format("%s is running ......", appName));
  messageLoops[isAddOnMaster]->run();
  if (!hasOnlyOne())
    messageLoops[!isAddOnMaster]->run();
  log->info(DevHelper::format("%s quit", appName));
}
