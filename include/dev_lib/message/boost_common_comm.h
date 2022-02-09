#ifndef __DEV_LIB_MESSAGE_BOOST_COMMON_COMM_H__
#define __DEV_LIB_MESSAGE_BOOST_COMMON_COMM_H__

#include "dev_lib/message/comm_message.h"
#include "dev_lib/log/log_harness.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/read.hpp>
#include <memory>
#include <functional>
#include <array>

class CommMessage;
template <typename T>
class BoostCommonComm
{
public:
  typedef std::vector<uint8_t> data_type;
  using io_service = boost::asio::io_service;
  using HandleAfterReadCallback = std::function<void (const data_type&)>;
  BoostCommonComm(io_service& io) : impl(io) {}
  virtual ~BoostCommonComm() { destroy(); }
  std::shared_ptr<CommMessage> init(const char* argv1, unsigned int argv2);

protected:
  mutable T impl;
  std::string argv1;
  unsigned int argv2;

private:
  virtual bool hasInit() const = 0;
  virtual void doInit() = 0;
  data_type read(size_t size) const;
  void init();
  void reInit();
  void cancel();
  void close();
  void destroy();
  void write(const data_type& data);
  void asyncRead(HandleAfterReadCallback lpfnHandleAfterRead);
  void doRead(HandleAfterReadCallback lpfnHandleAfterRead, boost::system::error_code ec, std::size_t readSize);
  std::array<uint8_t, 1024> readContent;
};

template <typename T>
inline std::shared_ptr<CommMessage> BoostCommonComm<T>::init(const char* argv1, unsigned int argv2)
{
  this->argv1 = argv1;
  this->argv2 = argv2;
  init();
  return std::make_shared<CommMessage>(
    std::bind(&BoostCommonComm<T>::hasInit, this),
    std::bind(&BoostCommonComm<T>::reInit, this),
    std::bind(&BoostCommonComm<T>::write, this, std::placeholders::_1),
    std::bind(&BoostCommonComm<T>::asyncRead, this, std::placeholders::_1),
    std::bind(&BoostCommonComm<T>::read, this, std::placeholders::_1));
}

template <typename T>
inline void BoostCommonComm<T>::init()
{
  doInit();
  if (hasInit())
    LOG(INFO) << "Common comm initialized: " << argv1 << "(" << argv2 << ")";
  else
    LOG(ERROR) << "Common comm can't init: " << argv1 << "(" << argv2 << ")";
}

template <typename T>
inline void BoostCommonComm<T>::reInit()
{
  destroy();
  init();
}

template <typename T>
inline void BoostCommonComm<T>::destroy()
{
  if (hasInit())
    close();
}

template <typename T>
inline void BoostCommonComm<T>::close()
{
  cancel();
  impl.close();
}

template <typename T>
inline void BoostCommonComm<T>::cancel()
{
  impl.cancel();
}

template <typename T>
inline void BoostCommonComm<T>::write(const data_type& data)
{
  boost::system::error_code ec;
  impl.write_some(boost::asio::buffer(data), ec);
  if (ec)
    LOG(ERROR) << ec.message();
}

template <typename T>
inline typename BoostCommonComm<T>::data_type BoostCommonComm<T>::read(size_t size) const
{
  assert(false);
  return data_type();
}

template <typename T>
inline void BoostCommonComm<T>::asyncRead(HandleAfterReadCallback lpfnHandleAfterRead)
{
  impl.async_read_some(boost::asio::buffer(readContent),
    std::bind(&BoostCommonComm<T>::doRead, this, lpfnHandleAfterRead, std::placeholders::_1, std::placeholders::_2));
}

template <typename T>
inline void BoostCommonComm<T>::doRead(HandleAfterReadCallback lpfnHandleAfterRead, boost::system::error_code ec, std::size_t readSize)
{
  if (ec)
    LOG(ERROR) << ec.message();
  else
    lpfnHandleAfterRead(data_type(readContent.begin(), readContent.begin() + readSize));

  asyncRead(lpfnHandleAfterRead);
}

#endif
