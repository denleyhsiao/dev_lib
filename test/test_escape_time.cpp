#include "dev_lib/escape_time.h"
#include <boost/thread.hpp>
#include <gtest/gtest.h>
#include <sstream>

static long DELAY_MILLI_SECONDS = 2;

TEST(EscapeTime, stringstream)
{
  std::stringstream ss;
  {
    EscapeTime escapeTime(ss);
    boost::thread::sleep(EscapeTime::current() + boost::posix_time::milliseconds(DELAY_MILLI_SECONDS));
    ASSERT_EQ(DELAY_MILLI_SECONDS, escapeTime.total_milliseconds());
  }
  // ASSERT_EQ("Execute time cost: 2 ms.\n", ss.str());
}

TEST(EscapeTime, cout)
{
  EscapeTime escapeTime;
  boost::thread::sleep(EscapeTime::current() + boost::posix_time::milliseconds(DELAY_MILLI_SECONDS));
}
