#include "dev_lib/boost_helper.h"
#include "dev_lib/dev_helper.h"
#include <gtest/gtest.h>

typedef BoostHelper::floats_type floats_type;
typedef BoostHelper::strings_type strings_type;

TEST(BoostHelper, splitToString)
{
  ASSERT_EQ(strings_type({"7:30", "8:30"}), BoostHelper::splitToString("7:30~8:30", '~'));
}

TEST(BoostHelper, splitToFloat)
{
  ASSERT_EQ(floats_type({1.2,3.4,5.6,7.8,9.0}), BoostHelper::splitToFloat("1.2,3.4,5.6,7.8,9.0"));
}

TEST(BoostHelper, splitWithSpace)
{
  ASSERT_EQ(floats_type({1.2,3.4,5.6,7.8,9.0}), BoostHelper::splitToFloat("1.2 3.4 5.6 7.8 9.0", ' '));
}

TEST(BoostHelper, splitWithInf)
{
  float inf = DevHelper::inf;
  ASSERT_EQ(floats_type({1.2,3.4,inf,5.6,7.8,9.0,inf}), BoostHelper::splitToFloat("1.2,3.4,inf,5.6,7.8,9.0,inf"));
}
