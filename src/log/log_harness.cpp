#include "dev_lib/log/log_harness.h"
#include "dev_lib/dev_helper.h"
#include <gflags/gflags.h>
#include <string>

LogHarness::LogHarness(int argc, char** argv)
{
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  google::InstallFailureWriter([](const char* data, size_t size) {
    LOG(WARNING) << std::string(data, size);
  });
}

LogHarness::~LogHarness()
{
  google::ShutdownGoogleLogging();
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
