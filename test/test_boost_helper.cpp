#include "dev_lib/boost_helper.h"
#include "dev_lib/dev_helper.h"
#include <gtest/gtest.h>

typedef BoostHelper::floats_type floats_type;

TEST(BoostHelperTest, splitToFloat)
{
  ASSERT_EQ(floats_type({1.2,3.4,5.6,7.8,9.0}), BoostHelper::splitToFloat("1.2,3.4,5.6,7.8,9.0"));
}

TEST(BoostHelperTest, splitWithSpace)
{
  ASSERT_EQ(floats_type({1.2,3.4,5.6,7.8,9.0}), BoostHelper::splitToFloat("1.2 3.4 5.6 7.8 9.0", ' '));
}

TEST(BoostHelperTest, splitWithInf)
{
  float inf = DevHelper::inf;
  ASSERT_EQ(floats_type({1.2,3.4,inf,5.6,7.8,9.0,inf}), BoostHelper::splitToFloat("1.2,3.4,inf,5.6,7.8,9.0,inf"));
}

TEST(BoostHelperTest, getTime)
{
  static const unsigned int HOUR = 1, MINUTE = 2, START_SECOND = 3, ESCAPE_SECOND = 4;
  boost::posix_time::time_duration start(HOUR, MINUTE, START_SECOND);
  boost::posix_time::time_duration end(HOUR, MINUTE, START_SECOND + ESCAPE_SECOND);
  ASSERT_EQ(BoostHelper::getTime(start) + ESCAPE_SECOND * 1000, BoostHelper::getTime(end));
}

TEST(BoostHelperTest, crc16)
{
  ASSERT_EQ(0xFFFF, BoostHelper::crc16({}));
  ASSERT_EQ(0x8240, BoostHelper::crc16({0x3, 0x7}));
  ASSERT_EQ(0xA80D, BoostHelper::crc16({0x10, 0x20}));
  ASSERT_EQ(0x1A3C, BoostHelper::crc16({0x50, 0x98}));
}
