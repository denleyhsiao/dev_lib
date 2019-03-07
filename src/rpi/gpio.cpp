#include "dev_lib/rpi/gpio.h"

unsigned int GPIO::pin() const
{
  return comm.pin();
}

bool GPIO::init(int mode)
{
  return (comm.init(mode) == 0);
}

void GPIO::write(bool isVih)
{
  comm.write(isVih ? VIH : VIL);
}

bool GPIO::read() const
{
  return (comm.read() == VIH);
}

int GPIO::detectedRising(void (* callback)())
{
  return comm.detectedRising(callback);
}

int GPIO::detectedFalling(void (* callback)())
{
  return comm.detectedFalling(callback);
}

int GPIO::detectedBoth(void (* callback)())
{
  return comm.detectedBoth(callback);
}

int GPIO::detectedSetup(void (* callback)())
{
  return comm.detectedSetup(callback);
}
