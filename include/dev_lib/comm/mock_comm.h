#ifndef __DEV_LIB_COMM_MOCK_COMM_H__
#define __DEV_LIB_COMM_MOCK_COMM_H__

#include "dev_lib/comm/comm.h"
#include <memory>

class MockComm : public Comm
{
public:
  typedef Comm::data_type data_type;
  virtual bool hasInit() const { return true; }
  virtual bool init(const char* serialPort, unsigned int serialBaudrate, HandleInitCallback lpfnHandleInit);
  virtual void reopen() { }
  virtual data_type read(size_t size) const;
  virtual void asyncRead(HandleAfterReadCallback lpfnHandleAfterRead, const data_type& delim) { }

private:
  virtual void doWrite(const data_type& data) { }
};

#endif
