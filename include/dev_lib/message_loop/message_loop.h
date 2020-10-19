#ifndef __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_H__

#include <functional>
#include <memory>

class Log;
class MessageLoop
{
public:
  using quit_t = std::function<void(std::shared_ptr<Log> log, int number)>;
  virtual ~MessageLoop() {}
  virtual void run(quit_t quit) = 0;

};

#endif
