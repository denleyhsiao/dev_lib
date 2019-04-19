#include "dev_lib/dev_helper.h"
#include <gtest/gtest.h>

TEST(DevHelper, format)
{
  std::string actualValue = DevHelper::format("My name is %s, and age is %d", "Denley Hsiao", 28);
  ASSERT_EQ("My name is Denley Hsiao, and age is 28", actualValue);
}
