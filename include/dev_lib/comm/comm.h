#ifndef __DEV_LIB_COMM_COMM_H__
#define __DEV_LIB_COMM_COMM_H__

#include <stdint.h>
#include <cstddef>
#include <vector>
#include <memory>
#include <functional>

class Log;
class Comm
{
public:
  typedef std::vector<uint8_t> data_type;
  typedef std::function<void (const data_type&)> cb_read_type;
  virtual ~Comm() {}
  virtual bool hasInit() const = 0;
  virtual bool init(const char* serialPort, unsigned int serialBaudrate) = 0;
  virtual data_type read(size_t size) const = 0;
  virtual void asyncRead(cb_read_type cbRead, const data_type& delim) = 0;
  void write(const data_type& data);

protected:
  Comm(std::shared_ptr<Log> log) : log(log) { }
  std::shared_ptr<Log> log;

private:
  virtual void doWrite(const data_type& data) = 0;
};

#endif
