#include "dev_lib/rpi/gpio_comm.h"
  
int GPIOComm::init(int mode)
{
  int result = wiringPiSetup();
  if (result == 0)
    pinMode(pin, mode);
  return result;
}

void GPIOComm::write(int value)
{
  digitalWrite(pin, value);
}

int GPIOComm::read() const
{
  return digitalRead(pin);
}

int GPIOComm::detectedRising(void (* callback)())
{
  return detected(INT_EDGE_RISING, callback);
}

int GPIOComm::detectedFalling(void (* callback)())
{
  return detected(INT_EDGE_FALLING, callback);
}

int GPIOComm::detectedBoth(void (* callback)())
{
  return detected(INT_EDGE_BOTH, callback); 
}

int GPIOComm::detectedSetup(void (* callback)())
{
  return detected(INT_EDGE_SETUP, callback); 
}

int GPIOComm::detected(unsigned int eventType, void (* callback)())
{
  return wiringPiISR(pin, eventType, callback);
}
