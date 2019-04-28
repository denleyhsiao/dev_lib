#include "dev_lib/escape_time.h"
#include <iostream>

EscapeTime::EscapeTime() : begin(boost::get_system_time())
{
}

EscapeTime::~EscapeTime()
{
  std::cout << "Execute time cost: " << (boost::get_system_time()-begin).total_milliseconds() << " ms." << std::endl;
}
