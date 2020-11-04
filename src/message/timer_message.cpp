#include "dev_lib/message/timer_message.h"

TimerMessage::TimerMessage(HandleTimerCallback lpfnHandleTimer, RedoTimerCallback lpfnRedoTimer, CancelTimerCallback lpfnCancelTimer)
  : lpfnHandleTimer(lpfnHandleTimer), lpfnRedoTimer(lpfnRedoTimer), lpfnCancelTimer(lpfnCancelTimer)
{

}

void TimerMessage::execute()
{
  if (lpfnHandleTimer)
    lpfnHandleTimer(std::bind(&TimerMessage::redo, this));
}

void TimerMessage::redo()
{
  if (lpfnRedoTimer)
    lpfnRedoTimer();
}

void TimerMessage::cancel()
{
  if (lpfnCancelTimer)
    lpfnCancelTimer();
}
