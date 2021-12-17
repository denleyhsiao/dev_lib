#include "dev_lib/log/log_harness.h"
#include <gflags/gflags.h>

LogHarness::LogHarness(int argc, char** argv)
{
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
}

LogHarness::~LogHarness()
{
  google::ShutdownGoogleLogging();
}
