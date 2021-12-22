#include "dev_lib/log/log_harness.h"
#include "dev_lib/dev_helper.h"
#include <gflags/gflags.h>
#include <iomanip>
#include <string>

void CustomPrefix(std::ostream& s, const LogMessageInfo& l, void*)
{
   s << l.severity[0]
   << std::setw(4) << 1900 + l.time.year()
   << std::setw(2) << 1 + l.time.month()
   << std::setw(2) << l.time.day()
   << ' '
   << std::setw(2) << l.time.hour() << ':'
   << std::setw(2) << l.time.min()  << ':'
   << std::setw(2) << l.time.sec();
}

LogHarness::LogHarness(int argc, char** argv)
{
  google::InitGoogleLogging(argv[0], &CustomPrefix);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InstallFailureSignalHandler();
  google::InstallFailureWriter(&LogHarness::handleSingal);
}

LogHarness::~LogHarness()
{
  google::ShutdownGoogleLogging();
}

void LogHarness::handleSingal(const char* data, int size)
{
  LOG(FATAL) << std::string(data, size);
}

Precision::Precision(float value, size_t precision /* = 3 */) : value(value), precision(precision)
{

}

Hex::Hex(uint8_t value) : value(value)
{

}

std::ostream& operator<<(std::ostream& out, uint8_t value)
{
  out << static_cast<unsigned int>(value);
  return out;
}

std::ostream& operator<<(std::ostream& out, const Precision& value)
{
  out << DevHelper::toString(value.value, value.precision);
  return out;
}

std::ostream& operator<<(std::ostream& out, const Hex& value)
{
  std::ios::fmtflags flags(out.flags());
  out << std::hex << std::setw(2)<<std::setfill('0') << value.value;
  out.flags(flags);
  return out;
}
