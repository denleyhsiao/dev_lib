#ifndef __DEV_LIB_GPIO_MOCK_GPIO_H__
#define __DEV_LIB_GPIO_MOCK_GPIO_H__

#include "dev_lib/gpio/gpio.h"

class MockGPIO : public GPIO
{
public:
  static std::shared_ptr<GPIO> create(unsigned int number);
  MockGPIO(unsigned int number);
  virtual unsigned int number() const;
  virtual bool read() const;
  virtual void write(bool isHigh);
  virtual int detectedBoth(void (* callback)());

private:
  virtual bool doInit(bool isOutput);
  int no;
  bool isHigh;
};

#endif
