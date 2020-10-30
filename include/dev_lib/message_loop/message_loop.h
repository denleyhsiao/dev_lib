#ifndef __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_H__

#include <functional>
#include <tuple>

class MessageLoop
{
public:
  using CancelMessage = std::function<void()>;
  using RedoMessage = std::function<void()>;
  using HandleMessage = std::function<void(RedoMessage)>;
  MessageLoop(bool isMaster = false) : thisIsMaster(isMaster) {}
  bool isMaster() const { return thisIsMaster; }
  virtual ~MessageLoop() {}
  virtual std::tuple<CancelMessage, RedoMessage> add(float delaySeconds, HandleMessage handleMessage) = 0;
  virtual void run() = 0;

private:
  bool thisIsMaster;
};

#endif
