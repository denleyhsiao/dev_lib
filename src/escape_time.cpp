#include "dev_lib/escape_time.h"

boost::posix_time::ptime EscapeTime::current()
{
  return boost::get_system_time();
}

EscapeTime::EscapeTime() : os(std::cout), begin(current())
{
}

EscapeTime::EscapeTime(std::ostream& os) : os(os), begin(current())
{
}

EscapeTime::~EscapeTime()
{
  print();
}

void EscapeTime::print() const
{
  os << "Execute time cost: " << total_milliseconds() << " ms." << std::endl;
}

long EscapeTime::total_milliseconds() const
{
  return (current() - begin).total_milliseconds();
}
