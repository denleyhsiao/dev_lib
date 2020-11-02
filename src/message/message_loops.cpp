#include "dev_lib/message/message_loops.h"
#include "dev_lib/message/message_loop.h"
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
    messageLoops[value->isMaster()] = value;
}

bool MessageLoops::hasInit() const
{
  return !messageLoops.empty();
}

bool MessageLoops::hasOnlyOne() const
{
  return (messageLoops.size() == 1);
}

std::shared_ptr<TimerMessage> MessageLoops::addTimer(const char* tip, float delaySeconds, HandleMessage handleMessage)
{
  log->info(DevHelper::format("Add message of %s: %.3f second(s)", tip, delaySeconds));
  return messageLoops[isAddOnMaster]->addTimer(delaySeconds, handleMessage);
}

void MessageLoops::run(const char* appName)
{
  assert(hasInit());
  log->info(DevHelper::format("%s is running......", appName));
  messageLoops[isAddOnMaster]->run();
  if (!hasOnlyOne())
    messageLoops[!isAddOnMaster]->run();
  log->info(DevHelper::format("%s quit", appName));
}
