#ifndef __DEV_LIB_MESSAGE_LOOP_MESSAGE_H__
#define __DEV_LIB_MESSAGE_LOOP_MESSAGE_H__

#include <functional>

class Message
{
public:
  using RedoMessage = std::function<void()>;
  using HandleMessage = std::function<void(RedoMessage)>;
  using CancelMessage = std::function<void()>;
  Message(HandleMessage handleMessage, RedoMessage redoMessage, CancelMessage cancelMessage);
  void execute();
  void redo();
  void cancel();

private:
  HandleMessage handleMessage;
  RedoMessage redoMessage;
  CancelMessage cancelMessage;
};

#endif
