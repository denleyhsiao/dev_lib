#include "dev_lib/dev_helper.h"
#include <gtest/gtest.h>

typedef DevHelper::uints_type   uints_type;
typedef DevHelper::floats_type  floats_type;
typedef DevHelper::strings_type strings_type;

TEST(DevHelperTest, format)
{
  std::string actualValue = DevHelper::format("My name is %s, and age is %d", "Denley Hsiao", 28);
  ASSERT_EQ("My name is Denley Hsiao, and age is 28", actualValue);
}

TEST(DevHelperTest, count)
{
  floats_type source = {1,2,2,3,3,3,4,4,4,4,5,5,5,5,5};
  floats_type::size_type length = source.size();
  floats_type::value_type flag = 2;
  ASSERT_EQ(2, DevHelper::count(source, flag, 0, length));
  ASSERT_EQ(2, DevHelper::count(source, flag, 1, length));
  ASSERT_EQ(1, DevHelper::count(source, flag, 2, length));
  ASSERT_EQ(0, DevHelper::count(source, flag, 3, length));

  flag = 5;
  ASSERT_EQ(5, DevHelper::count(source, flag, 0,  length));
  ASSERT_EQ(5, DevHelper::count(source, flag, 10, length));
  ASSERT_EQ(4, DevHelper::count(source, flag, 11, length));
  ASSERT_EQ(3, DevHelper::count(source, flag, 12, length));
  ASSERT_EQ(2, DevHelper::count(source, flag, 13, length));
  ASSERT_EQ(1, DevHelper::count(source, flag, 14, length));
  ASSERT_EQ(0, DevHelper::count(source, flag, 15, length));
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
  ASSERT_EQ("1,2,3", DevHelper::toString(uints_type({1,2,3}), ','));
  ASSERT_EQ("1-2-3", DevHelper::toString(uints_type({1,2,3}), '-'));
}

TEST(DevHelperTest, floatsToString)
{
  ASSERT_EQ("0.1", DevHelper::toString(floats_type({0.1})));
  ASSERT_EQ("0.1,2.3", DevHelper::toString(floats_type({0.1,2.3})));
  ASSERT_EQ("0.1,2.3,4.5,6.7,8.9", DevHelper::toString(floats_type({0.1,2.3,4.5,6.7,8.9})));
}

TEST(DevHelperTest, split)
{
  ASSERT_EQ(strings_type({"7:30", "8:30"}), DevHelper::split("7:30~8:30", '~'));
}

TEST(DevHelperTest, uintsToHex)
{
  ASSERT_EQ("A0010307", DevHelper::toHex(uints_type({0xA0, 0x01, 0x03, 0x07})));
}

TEST(DevHelperTest, stringToHex)
{
  ASSERT_EQ("343139", DevHelper::toHex("419"));
  ASSERT_EQ("414243", DevHelper::toHex("ABC"));
  ASSERT_EQ("383941", DevHelper::toHex("89A"));
  ASSERT_EQ("616263", DevHelper::toHex("abc"));
  ASSERT_EQ("383961", DevHelper::toHex("89a"));
}

TEST(DevHelperTest, crc)
{
  ASSERT_EQ(7, DevHelper::crc(1, {2,3,4}));
  ASSERT_EQ(12, DevHelper::crc(8, {9,19,29}));
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
