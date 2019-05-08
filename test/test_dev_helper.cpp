#include "dev_lib/dev_helper.h"
#include <gtest/gtest.h>

TEST(DevHelper, format)
{
  std::string actualValue = DevHelper::format("My name is %s, and age is %d", "Denley Hsiao", 28);
  ASSERT_EQ("My name is Denley Hsiao, and age is 28", actualValue);
}

TEST(DevHelperTest, floatToString)
{
  static const float source = 13.14159;
  ASSERT_EQ("13.1", DevHelper::toString(source));
  ASSERT_EQ("13.14", DevHelper::toString(source, 2));
  ASSERT_EQ("13.142", DevHelper::toString(source, 3));
  ASSERT_EQ("13.1416", DevHelper::toString(source, 4));
}

TEST(DevHelperTest, intsToString)
{
  typedef DevHelper::uints_type uints_type;
  ASSERT_EQ("1,2,3", DevHelper::toString(uints_type({1,2,3}), ','));
  ASSERT_EQ("1-2-3", DevHelper::toString(uints_type({1,2,3}), '-'));
}

TEST(DevHelperTest, floatsToString)
{
  typedef DevHelper::floats_type floats_type;
  ASSERT_EQ("0.1", DevHelper::toString(floats_type({0.1})));
  ASSERT_EQ("0.1,2.3", DevHelper::toString(floats_type({0.1,2.3})));
  ASSERT_EQ("0.1,2.3,4.5,6.7,8.9", DevHelper::toString(floats_type({0.1,2.3,4.5,6.7,8.9})));
}
