#ifndef __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_H__

class MessageLoop
{
public:
  virtual ~MessageLoop() {}
  virtual void run() = 0;

};

#endif
