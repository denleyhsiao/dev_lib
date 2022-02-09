#include "dev_lib/gpio/gpio.h"
#include <cassert>

GPIO::~GPIO()
{
  destroy();
}

bool GPIO::init(bool isOutput)
{
  bool result = doInit(isOutput);
  if (result)
    write(false);
  return result;
}

void GPIO::write(bool isHigh, const data_type& value)
{
  assert(false);
  write(isHigh);
}

void GPIO::destroy()
{
  if (read())
    write(false);
}
