#ifndef __DEV_LIB_RPI_GPIO_COMM_H__
#define __DEV_LIB_RPI_GPIO_COMM_H__

#include <wiringPi.h>

class GPIOComm
{
public:
  GPIOComm(unsigned int pin) : pin_(pin) {}
  unsigned int pin() const { return pin_; }
  int init(int mode);
  void write(int value);
  int read() const;
  int detectedRising(void (* callback)());
  int detectedFalling(void (* callback)());
  int detectedBoth(void (* callback)());
  int detectedSetup(void (* callback)());
  
private:
  int detected(unsigned int eventType, void (* callback)());
  unsigned int pin_;
};

#endif
