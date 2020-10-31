#include "dev_lib/message_loop/message.h"

Message::Message(HandleMessage handleMessage, RedoMessage redoMessage, CancelMessage cancelMessage)
  : handleMessage(handleMessage), redoMessage(redoMessage), cancelMessage(cancelMessage)
{

}

void Message::execute()
{
  if (handleMessage)
    handleMessage(std::bind(&Message::redo, this));
}

void Message::redo()
{
  if (redoMessage)
    redoMessage();
}

void Message::cancel()
{
  if (cancelMessage)
    cancelMessage();
}
