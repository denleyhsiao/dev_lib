#ifndef __DEV_LIB_BOOST_HELPER_H__
#define __DEV_LIB_BOOST_HELPER_H__

#include <string>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>

class BoostHelper
{
public:
  typedef std::vector<uint8_t>      uints_type;
  typedef std::vector<float>        floats_type;
  typedef std::vector<std::string>  strings_type;
  static uint16_t crc16(const uints_type& source);
  static bool readFile(const char* fileName, std::string& target);
  static floats_type splitToFloat(const char* value, const char delimiter = ',');
  static void sleep(float seconds);
  static std::string getFileName(const char* lastFileName);
  static std::string currentDateTime(const char* format = "%Y-%m-%d %H:%M:%S");
  static std::string currentTime();
  static std::string currentTimestamp();
  static std::string createUUID();
  static std::string toString(const boost::posix_time::time_duration& time);
  static std::string toString(const boost::posix_time::ptime& time);
  static std::string toString(const tm& time);
  static std::string toString(unsigned int time);
  static unsigned int toUint(const std::string& value);
  static bool toBool(const std::string& value);
  static float toFloat(const std::string& value);
  static unsigned int getTime(boost::posix_time::ptime time);
  static unsigned int getTime(boost::posix_time::time_duration time);
  static unsigned int getCurrentTime();
  static boost::posix_time::ptime getTime(unsigned int time);
  static boost::posix_time::ptime getTime(const std::string& time);
  static boost::posix_time::time_duration getTimeDuration(float seconds);
  static boost::posix_time::time_duration getTimeDuration(const std::string& time);
  static boost::posix_time::time_duration getCurrentTimeDuration();

private:
  static boost::posix_time::time_duration getCurrentTimeStamp();
  static boost::posix_time::ptime getCurrentDateTime();
};

#endif
