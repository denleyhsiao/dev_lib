#ifndef __DEV_LIB_COMM_COMMON_COMM_H__
#define __DEV_LIB_COMM_COMMON_COMM_H__

#include "dev_lib/comm/comm.h"

class CommonComm : public Comm
{
public:
  CommonComm();
  virtual void reopen() override;
  virtual bool hasInit() const override;
  virtual bool init(const char* argv1, unsigned int argv2, HandleInitCallback lpfnHandleInit) override = 0;
  virtual data_type read(size_t size) const override;
  virtual void asyncRead(HandleAfterReadCallback lpfnHandleAfterRead) override;

protected:
  std::shared_ptr<CommMessage> message;
private:
  virtual void doWrite(const data_type& data) override;
};

#endif
