#ifndef __DEV_LIB_COMM_COMM_H__
#define __DEV_LIB_COMM_COMM_H__

#include <stdint.h>
#include <cstddef>
#include <vector>
#include <memory>
#include <functional>

class CommMessage;
class Comm
{
public:
  typedef std::vector<uint8_t> data_type;
  using HandleAfterReadCallback = std::function<void (const data_type&)>;
  using HandleInitCallback = std::function<std::shared_ptr<CommMessage> (const char*, unsigned int)>;
  virtual ~Comm() {}
  virtual bool hasInit() const = 0;
  virtual bool init(const char* argv1, unsigned int argv2, HandleInitCallback lpfnHandleInit) = 0;
  virtual void reopen() = 0;
  virtual data_type read(size_t size) const = 0;
  virtual void asyncRead(HandleAfterReadCallback lpfnHandleAfterRead) = 0;
  void write(const data_type& data);

private:
  virtual void doWrite(const data_type& data) = 0;
};

#endif
