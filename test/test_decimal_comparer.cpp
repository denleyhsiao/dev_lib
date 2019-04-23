#include "dev_lib/decimal_comparer.h"
#include <gtest/gtest.h>

TEST(DecimalComparerTest, isEqual)
{
  ASSERT_TRUE( DecimalComparer::isEqual(1.0f, 1.0000099f));
  ASSERT_TRUE( DecimalComparer::isEqual(1.0f, 0.9999901f));
  ASSERT_FALSE(DecimalComparer::isEqual(1.0f, 1.00001f));
  ASSERT_FALSE(DecimalComparer::isEqual(1.0f, 0.99999f));
}
