#ifndef __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_THREAD_H__
#define __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_THREAD_H__

#include <boost/thread.hpp>
#include <memory>

class Log;
template <typename T>
class MessageLoopThread : public T
{
public:
  typedef typename T::quit_t quit_t;
  MessageLoopThread(std::shared_ptr<Log> log, bool isSync = true) : T(log), thread(nullptr), isSync(isSync) {}
  ~MessageLoopThread()
  {
    T::stop();
    join();
  }
  virtual void run(quit_t quit)
  {
    thread = std::make_shared<boost::thread>(&T::doRun, this, quit);
    if (isSync)
      join();
  }

private:
  void join()
  {
    if (thread && thread->joinable())
      thread->join();
  }
  std::shared_ptr<boost::thread> thread;
  bool isSync;
};

#endif
