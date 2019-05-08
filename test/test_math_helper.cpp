#include "dev_lib/math_helper.h"
#include <gtest/gtest.h>

TEST(MathHelperTest, distance)
{
  ASSERT_FLOAT_EQ(2 * sqrt(2), MathHelper::distance(1.0, 2.0, 3.0, 4.0, MathHelper::PI2));
}
