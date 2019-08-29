#ifndef __DEV_LIB_BOOST_HELPER_H__
#define __DEV_LIB_BOOST_HELPER_H__

#include <string>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>

class BoostHelper
{
public:
  typedef std::vector<float>  floats_type;
  typedef std::vector<std::string>  strings_type;
  static floats_type splitToFloat(const char* value, const char delimiter = ',');
  static void sleep(float seconds);
  static std::string currentDateTime(const char* format = "%Y-%m-%d %H:%M:%S");
  static std::string currentTime();
  static std::string currentTimestamp();
  static std::string createUUID();
  static std::string toString(const boost::posix_time::time_duration& time);
  static boost::posix_time::time_duration getTime(const std::string& time);
  static boost::posix_time::time_duration getCurrentTime();

private:
  static boost::posix_time::ptime getCurrentDateTime();
};

#endif
