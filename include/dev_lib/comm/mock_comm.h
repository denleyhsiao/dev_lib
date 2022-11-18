#ifndef __DEV_LIB_COMM_MOCK_COMM_H__
#define __DEV_LIB_COMM_MOCK_COMM_H__

#include "dev_lib/comm/comm.h"

class MockComm : public Comm
{
public:
  virtual bool hasInit() const override { return true; }
  virtual bool init(const char* argv1, unsigned int argv2, HandleInitCallback lpfnHandleInit) override;
  virtual void reopen() override { }
  virtual data_type read(size_t size) const override;
  virtual void asyncRead(HandleAfterReadCallback lpfnHandleAfterRead) override { }

private:
  virtual void doWrite(const data_type& data) override { }
};

#endif
