#ifndef __DEV_LIB_MESSAGE_SERIAL_PORT_MESSAGE_H__
#define __DEV_LIB_MESSAGE_SERIAL_PORT_MESSAGE_H__

#include <stdint.h>
#include <vector>
#include <functional>

class SerialPortMessage
{
public:
  typedef std::vector<uint8_t> data_type;
  using HasInitCallback = std::function<bool()>;
  using ReInitCallback = std::function<void()>;
  using WriteCallback = std::function<void(const data_type&)>;
  using HandleAfterReadCallback = std::function<void (const data_type&)>;
  using AsyncReadCallback = std::function<void(HandleAfterReadCallback, const data_type&)>;
  using ReadCallback = std::function<data_type(size_t)>;
  SerialPortMessage(HasInitCallback lpfnHasInit, ReInitCallback lpfnReInit,
    WriteCallback lpfnWrite, AsyncReadCallback lpfnAsyncRead, ReadCallback lpfnRead);
  bool hasInit() const;
  void reInit();
  void write(const data_type& data);
  void asyncRead(HandleAfterReadCallback lpfnHandleAfterRead, const data_type& delim);
  data_type read(size_t size) const;

private:
  HasInitCallback lpfnHasInit;
  ReInitCallback lpfnReInit;
  WriteCallback lpfnWrite;
  AsyncReadCallback lpfnAsyncRead;
  ReadCallback lpfnRead;
};

#endif
