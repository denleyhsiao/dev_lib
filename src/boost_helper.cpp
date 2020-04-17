#include "dev_lib/boost_helper.h"
#include "dev_lib/dev_helper.h"
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <sstream>
#include <algorithm>

std::string BoostHelper::toString(const boost::posix_time::time_duration& time)
{
  return boost::posix_time::to_simple_string(time);
}

std::string BoostHelper::toString(const tm& time)
{
  return toString(boost::posix_time::ptime_from_tm(time).time_of_day());
}

unsigned int BoostHelper::toUint(const std::string& value)
{
  return atoi(value.c_str());
}

bool BoostHelper::toBool(const std::string& value)
{
  return (value == "true");
}

float BoostHelper::toFloat(const std::string& value)
{
  return atof(value.c_str());
}

boost::posix_time::time_duration BoostHelper::getTime(const std::string& time)
{
  return boost::posix_time::duration_from_string(time);
}

BoostHelper::floats_type BoostHelper::splitToFloat(const char* value, const char delimiter /* = ',' */)
{
  floats_type result = floats_type();
  strings_type values = DevHelper::split(value, delimiter);
  for(const auto& value: values)
    result.push_back(boost::lexical_cast<float>(value));
  return result;
}

void BoostHelper::sleep(float seconds)
{
  boost::thread::sleep(boost::get_system_time() + boost::posix_time::milliseconds(seconds*1000));
}

std::string BoostHelper::currentDateTime(const char* format /* = "%Y-%m-%d %H:%M:%S" */)
{
  std::ostringstream oss;
  static std::locale loc(oss.getloc(), new boost::posix_time::time_facet(format));
  oss.imbue(loc);
  oss << getCurrentDateTime();
  return oss.str();
}

std::string BoostHelper::currentTime()
{
  return toString(getCurrentTime());
}

boost::posix_time::time_duration BoostHelper::getCurrentTime()
{
  return getCurrentDateTime().time_of_day();
}

boost::posix_time::ptime BoostHelper::getCurrentDateTime()
{
  return boost::get_system_time() + boost::posix_time::hours(8);
}

std::string BoostHelper::currentTimestamp()
{
  boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));
  boost::posix_time::time_duration time_from_epoch = boost::posix_time::microsec_clock::local_time() - epoch;
  return DevHelper::format("%ld000", time_from_epoch.total_seconds());
}

std::string BoostHelper::createUUID()
{
  std::string result = boost::uuids::to_string(boost::uuids::random_generator()());
  std::string::iterator begin = std::remove_if(result.begin(), result.end(), [](char ch){ return (ch == '-'); });
  result.erase(begin, result.end());
  return result;
}
