#include "dev_lib/boost_helper.h"
#include <boost/lexical_cast.hpp>
#include <iterator>
#include <algorithm>

BoostHelper::floats_type BoostHelper::split(const char* value, const char delimiter /* = ',' */)
{
  static const char SPACE_FLAG = ' ';
  floats_type result = floats_type();
  std::string source = value;
  if (delimiter != SPACE_FLAG)
    std::replace(source.begin(), source.end(), delimiter, SPACE_FLAG);

  std::istringstream iss(source);
  std::vector<std::string> values((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
  for (std::string value: values)
    result.push_back(boost::lexical_cast<float>(value));
  return result;
}
