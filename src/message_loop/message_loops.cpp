#include "dev_lib/message_loop/message_loops.h"
#include "dev_lib/message_loop/boost_message_loop.h"
#include "dev_lib/message_loop/message_loop_thread.h"
#include "dev_lib/log/log.h"
#include "dev_lib/dev_helper.h"
#include <cassert>

MessageLoops::MessageLoops() : masterMessageLoop(nullptr), slaveMessageLoop(nullptr), log(nullptr)
{
}

void MessageLoops::init(std::shared_ptr<MessageLoop> messageLoop, std::shared_ptr<Log> log)
{
  assert(messageLoop->isMaster());
  slaveMessageLoop = std::make_shared<MessageLoopThread<BoostMessageLoop> >(
    std::bind(&MessageLoops::quit, this, std::placeholders::_1));
  masterMessageLoop = messageLoop;
  this->log = log;
}

bool MessageLoops::hasInit() const
{
  return (masterMessageLoop != nullptr && slaveMessageLoop != nullptr);
}

void MessageLoops::quit(int number) const
{
  log->info(DevHelper::format("Received quit with signal %d", number));
}

void MessageLoops::run(const char* appName)
{
  assert(hasInit());
  log->info(DevHelper::format("%s is running......", appName));
  slaveMessageLoop->run();
  masterMessageLoop->run();
  log->info(DevHelper::format("%s quit", appName));
}
