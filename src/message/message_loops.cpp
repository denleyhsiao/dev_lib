#include "dev_lib/message/message_loops.h"
#include "dev_lib/message/message_loop.h"
#include "dev_lib/log/log.h"
#include "dev_lib/dev_helper.h"
#include <cassert>

MessageLoops::MessageLoops() : masterMessageLoop(nullptr), slaveMessageLoop(nullptr), log(nullptr)
{
}

void MessageLoops::init(std::shared_ptr<Log> log, std::shared_ptr<MessageLoop> first, std::shared_ptr<MessageLoop> second)
{
  assert(first->isMaster());
  slaveMessageLoop = second;
  masterMessageLoop = first;
  this->log = log;
}

bool MessageLoops::hasInit() const
{
  return (masterMessageLoop != nullptr && slaveMessageLoop != nullptr);
}

std::shared_ptr<Message> MessageLoops::add(const char* tip, float delaySeconds, HandleMessage handleMessage)
{
  log->info(DevHelper::format("Add message of %s: %.3f second(s)", tip, delaySeconds));
  return slaveMessageLoop->add(delaySeconds, handleMessage);
}

void MessageLoops::run(const char* appName)
{
  assert(hasInit());
  log->info(DevHelper::format("%s is running......", appName));
  slaveMessageLoop->run();
  masterMessageLoop->run();
  log->info(DevHelper::format("%s quit", appName));
}
