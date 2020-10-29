#ifndef __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_H__
#define __DEV_LIB_MESSAGE_LOOP_MESSAGE_LOOP_H__

class MessageLoop
{
public:
  MessageLoop(bool isMaster) : thisIsMaster(isMaster) {}
  bool isMaster() const { return thisIsMaster; }
  virtual ~MessageLoop() {}
  virtual void run() = 0;

private:
  bool thisIsMaster;
};

#endif
