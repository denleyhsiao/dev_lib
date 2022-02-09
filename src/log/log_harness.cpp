#include "dev_lib/log/log_harness.h"
#include "dev_lib/dev_helper.h"
#include <gflags/gflags.h>
#include <string>

LogHarness::LogHarness(int argc, char** argv)
{
  google::InitGoogleLogging(argv[0]);
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
  return out << static_cast<unsigned int>(value);
}

std::ostream& operator<<(std::ostream& out, const Precision& value)
{
  return out << DevHelper::toString(value.value, value.precision);
}

std::ostream& operator<<(std::ostream& out, const Hex& value)
{
  return DevHelper::doToHex(out, value.value);
}
