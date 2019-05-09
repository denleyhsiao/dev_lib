#include "dev_lib/boost_helper.h"
#include "dev_lib/dev_helper.h"
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <iterator>
#include <algorithm>

BoostHelper::floats_type BoostHelper::split(const char* value, const char delimiter /* = ',' */)
{
  floats_type result = floats_type();
  std::string source = value;
  if (delimiter != DevHelper::SPACE_FLAG)
    std::replace(source.begin(), source.end(), delimiter, DevHelper::SPACE_FLAG);

  std::istringstream iss(source);
  std::for_each(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
    [&result](const std::string& value){ result.push_back(boost::lexical_cast<float>(value)); });
  return result;
}

void BoostHelper::sleep(long msTime)
{
  boost::thread::sleep(boost::get_system_time() + boost::posix_time::milliseconds(msTime));
}
