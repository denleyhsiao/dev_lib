#include "dev_lib/message_loop/boost_message_loop.h"
#include "dev_lib/log/log.h"
#include <boost/asio.hpp>
#include <cassert>

BoostMessageLoop::BoostMessageLoop(std::shared_ptr<Log> log, quit_t quit) : log(log), quit(quit)
{

}

BoostMessageLoop::~BoostMessageLoop()
{
  stop();
}

void BoostMessageLoop::run()
{
  doRun();
}

void BoostMessageLoop::doRun()
{
  boost::asio::signal_set signal_set(io, SIGINT);
  signal_set.async_wait([this](const boost::system::error_code& ec, int number) {
    this->doStop();
    this->quit(this->log, number);
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
