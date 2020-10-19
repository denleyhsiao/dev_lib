#include "dev_lib/message_loop/boost_message_loop.h"
#include "dev_lib/log/log.h"
#include <boost/asio.hpp>
#include <cassert>

BoostMessageLoop::BoostMessageLoop(std::shared_ptr<Log> log) : log(log)
{

}

BoostMessageLoop::~BoostMessageLoop()
{
  stop();
}

void BoostMessageLoop::run(quit_t quit)
{
  doRun(quit);
}

void BoostMessageLoop::doRun(quit_t quit)
{
  boost::asio::signal_set signal_set(io, SIGINT);
  signal_set.async_wait([this, quit](const boost::system::error_code& ec, int number) {
    this->doStop();
    quit(this->log, number);
  });
  io.run();
}

void BoostMessageLoop::stop()
{
  if (!io.stopped())
    doStop();
}

void BoostMessageLoop::doStop()
{
  io.stop();
}
