#ifndef __DEV_LIB_COMM_MOCK_COMM_H__
#define __DEV_LIB_COMM_MOCK_COMM_H__

#include "dev_lib/comm/comm.h"
#include <memory>

class MockComm : public Comm
{
public:
  typedef Comm::data_type data_type;
  static std::shared_ptr<Comm> create(std::shared_ptr<Log> log);
  virtual bool hasInit() const { return true; }
  virtual bool init(const char* serialPort, unsigned int serialBaudrate);
  virtual data_type read(size_t size) const;
  virtual data_type read(size_t size, bool needSleep) const;

private:
  MockComm(std::shared_ptr<Log> log) : Comm(log) { }
  virtual void doWrite(const data_type& data) { }
};

#endif
