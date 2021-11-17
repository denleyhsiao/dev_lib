#include "dev_lib/gpio/mock_gpio.h"

std::shared_ptr<GPIO> MockGPIO::create(std::shared_ptr<Log> log, unsigned int number, unsigned int count, const char* port, unsigned int baudrate)
{
  return std::make_shared<MockGPIO>(number);
}

MockGPIO::MockGPIO(unsigned int number) : no(number), isHigh(false)
{
}

unsigned int MockGPIO::number() const
{
  return no;
}

bool MockGPIO::doInit(bool isOutput)
{
  return true;
}

bool MockGPIO::read() const
{
  return isHigh;
}

void MockGPIO::write(bool isHigh)
{
  this->isHigh = isHigh;
}

int MockGPIO::detectedBoth(void (* callback)())
{
  return 0;
}
