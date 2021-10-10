#include "dev_lib/dev_helper.h"
#include <gtest/gtest.h>

typedef DevHelper::uints_type   uints_type;
typedef DevHelper::strings_type strings_type;

TEST(DevHelperTest, format)
{
  std::string actualValue = DevHelper::format("My name is %s, and age is %d", "Denley Hsiao", 28);
  ASSERT_EQ("My name is Denley Hsiao, and age is 28", actualValue);
}

TEST(DevHelperTest, count)
{
  DevHelper::floats_type intensities = {47.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,100.000000,150.000000,150.000000,150.000000,150.000000,234.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,47.000000,47.000000,47.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,47.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,47.000000,47.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,47.000000,100.000000,150.000000,234.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,47.000000,47.000000,47.000000,47.000000,47.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,47.000000,47.000000,47.000000,47.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,100.000000,234.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,47.000000,47.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,47.000000,100.000000,150.000000,150.000000,234.000000,47.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,47.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000,100.000000,150.000000,150.000000,150.000000,150.000000,234.000000,47.000000,100.000000,234.000000,100.000000,150.000000,234.000000,47.000000,100.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,150.000000,234.000000};
  ASSERT_EQ(46, DevHelper::count(intensities, 150, 1, 48));
}

TEST(DevHelperTest, sum)
{
  ASSERT_EQ(0xAB, DevHelper::sum({0xA0, 0x01, 0x03, 0x07}));
}

TEST(DevHelperTest, floatToString)
{
  static const float source = 13.14159;
  ASSERT_EQ("13.1", DevHelper::toString(source, 1));
  ASSERT_EQ("13.14", DevHelper::toString(source, 2));
  ASSERT_EQ("13.142", DevHelper::toString(source, 3));
  ASSERT_EQ("13.1416", DevHelper::toString(source, 4));
}

TEST(DevHelperTest, increase)
{
  uints_type source = {1,3,5};
  ASSERT_EQ(uints_type({3,5,7}), DevHelper::increase(source, 2));
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

TEST(DevHelperTest, split)
{
  ASSERT_EQ(strings_type({"7:30", "8:30"}), DevHelper::split("7:30~8:30", '~'));
}

TEST(DevHelperTest, convertToHex)
{
  DevHelper::uints_type source = {0xA0, 0x01, 0x03, 0x07};
  ASSERT_EQ("A0010307", DevHelper::convertToHex(source));
}

TEST(DevHelperTest, stringConvertToHex)
{
  ASSERT_EQ("343139", DevHelper::convertToHex("419"));
}

TEST(DevHelperTest, mergeTo16)
{
  static const uint8_t low = 0x56;
  static const uint8_t high = 0xFF;
  static const uint16_t expectedValue = 0xFF56;
  ASSERT_EQ(expectedValue, DevHelper::mergeTo16(high, low));
  ASSERT_EQ(high, DevHelper::getHigh(expectedValue));
  ASSERT_EQ(low, DevHelper::getLow(expectedValue));
}

TEST(DevHelperTest, mergeTo8)
{
  ASSERT_EQ(0x56, DevHelper::mergeTo8(0x05, 0x06));
}
