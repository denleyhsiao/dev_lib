#ifndef __DEV_LIB_RPI_GPIO_H__
#define __DEV_LIB_RPI_GPIO_H__

#include "dev_lib/rpi/gpio_comm.h"

class GPIO
{
public:
  GPIO(unsigned int pin) : comm(pin) {}
  bool init(int mode); 
  bool read() const;
  void write(bool isVih);
  int detectedRising(void (* callback)());
  int detectedFalling(void (* callback)());
  int detectedBoth(void (* callback)());
  int detectedSetup(void (* callback)());
  
private:
  enum {VIH=0, VIL=1};
  GPIOComm comm;
};

#endif
