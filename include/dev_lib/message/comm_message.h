#ifndef __DEV_LIB_MESSAGE_COMM_MESSAGE_H__
#define __DEV_LIB_MESSAGE_COMM_MESSAGE_H__

#include <stdint.h>
#include <vector>
#include <functional>

class CommMessage
{
public:
  typedef std::vector<uint8_t> data_type;
  using HasInitCallback = std::function<bool()>;
  using ReInitCallback = std::function<void()>;
  using WriteCallback = std::function<void(const data_type&)>;
  using HandleAfterReadCallback = std::function<void (const data_type&)>;
  using AsyncReadCallback = std::function<void(HandleAfterReadCallback)>;
  using ReadCallback = std::function<data_type(size_t)>;
  CommMessage(HasInitCallback lpfnHasInit, ReInitCallback lpfnReInit,
    WriteCallback lpfnWrite, AsyncReadCallback lpfnAsyncRead, ReadCallback lpfnRead);
  bool hasInit() const;
  void reInit();
  void write(const data_type& data);
  void asyncRead(HandleAfterReadCallback lpfnHandleAfterRead);
  data_type read(size_t size) const;

private:
  HasInitCallback lpfnHasInit;
  ReInitCallback lpfnReInit;
  WriteCallback lpfnWrite;
  AsyncReadCallback lpfnAsyncRead;
  ReadCallback lpfnRead;
};

#endif
