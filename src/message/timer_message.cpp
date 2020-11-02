#include "dev_lib/message/timer_message.h"

TimerMessage::TimerMessage(HandleMessage handleMessage, RedoMessage redoMessage, CancelMessage cancelMessage)
  : handleMessage(handleMessage), redoMessage(redoMessage), cancelMessage(cancelMessage)
{

}

void TimerMessage::execute()
{
  if (handleMessage)
    handleMessage(std::bind(&TimerMessage::redo, this));
}

void TimerMessage::redo()
{
  if (redoMessage)
    redoMessage();
}

void TimerMessage::cancel()
{
  if (cancelMessage)
    cancelMessage();
}
