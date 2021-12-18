#include "dev_lib/log/log_harness.h"
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

void LogHarness::handleSingal(const char* data, size_t size)
{
  LOG(FATAL) << std::string(data, size);
}
