#ifndef __DEV_LIB_BOOST_HELPER_H__
#define __DEV_LIB_BOOST_HELPER_H__

#include <string>
#include <vector>

class BoostHelper
{
public:
  typedef std::vector<float>  floats_type;
  typedef std::vector<std::string>  strings_type;
  static floats_type splitToFloat(const char* value, const char delimiter = ',');
  static void sleep(long msTime);
  static std::string currentDateTime(const char* format = "%Y-%m-%d %H:%M:%S");
  static std::string currentTimestamp();
  static std::string createUUID();
};

#endif
