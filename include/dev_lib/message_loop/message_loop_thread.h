#ifndef __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_THREAD_H__
#define __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_THREAD_H__

#include <boost/thread.hpp>
#include <memory>

template <typename T>
class MessageLoopThread : public T
{
public:
  typedef typename T::quit_t quit_t;
  MessageLoopThread(quit_t quit, bool isMaster = false) : T(quit, isMaster), thread(nullptr) {}
  ~MessageLoopThread()
  {
    T::stop();
    join();
  }
  virtual void run()
  {
    thread = std::make_shared<boost::thread>(&T::doRun, this);
    if (T::isMaster())
      join();
  }

private:
  void join()
  {
    if (thread && thread->joinable())
      thread->join();
  }
  std::shared_ptr<boost::thread> thread;
};

#endif
