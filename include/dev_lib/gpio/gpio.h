#ifndef __DEV_LIB_GPIO_GPIO_H__
#define __DEV_LIB_GPIO_GPIO_H__

#include <stdint.h>
#include <vector>

class GPIO
{
public:
  typedef std::vector<uint8_t>  data_type;
  virtual ~GPIO();
  virtual unsigned int number() const = 0;
  virtual bool read() const = 0;
  virtual void write(bool isHigh) = 0;
  virtual void write(bool isHigh, const data_type& value);
  virtual int detectedBoth(void (* callback)()) = 0;
  bool init(bool isOutput);
  void destroy();

private:
  virtual bool doInit(bool isOutput) = 0;
};

#endif
