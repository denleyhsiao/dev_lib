#ifndef __DEV_LIB_MESSAGE_TIMER_MESSAGE_H__
#define __DEV_LIB_MESSAGE_TIMER_MESSAGE_H__

#include <functional>

class TimerMessage
{
public:
  using RedoTimerCallback = std::function<void()>;
  using HandleTimerCallback = std::function<void(RedoTimerCallback)>;
  using CancelTimerCallback = std::function<void()>;
  TimerMessage(HandleTimerCallback lpfnHandleTimer, RedoTimerCallback lpfnRedoTimer, CancelTimerCallback lpfnCancelTimer);
  void execute();
  void redo();
  void cancel();

private:
  HandleTimerCallback lpfnHandleTimer;
  RedoTimerCallback   lpfnRedoTimer;
  CancelTimerCallback lpfnCancelTimer;
};

#endif
