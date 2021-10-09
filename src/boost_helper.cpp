#include "dev_lib/boost_helper.h"
#include "dev_lib/dev_helper.h"
#include "dev_lib/os_helper.h"
#include <boost/crc.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <algorithm>

uint16_t BoostHelper::crc16(const uints_type& source)
{
  boost::crc_optimal<16, 0x8005, 0xFFFF, 0, true, true> crc;
  if (!source.empty())
    crc.process_bytes(&source.at(0), source.size());
  return crc.checksum();
}

bool BoostHelper::readFile(const char* fileName, std::string& target)
{
  bool result = false;
  std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
  if (ifs)
  {
    result = !result;
    target.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
}
  return result;
}

std::string BoostHelper::getFileName(const char* lastFileName)
{
  std::string moduleFileName = OSHelper::getModuleFileName();
  return (boost::filesystem::path(moduleFileName.c_str()).parent_path()/lastFileName).string();
}

std::string BoostHelper::toString(const boost::posix_time::time_duration& time)
{
  return boost::posix_time::to_simple_string(time);
}

std::string BoostHelper::toString(const boost::posix_time::ptime& time)
{
  return boost::posix_time::to_simple_string(time);
}

std::string BoostHelper::toString(const tm& time)
{
  return toString(boost::posix_time::ptime_from_tm(time));
}

std::string BoostHelper::toString(unsigned int time)
{
  return toString(boost::posix_time::from_time_t(time));
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

boost::posix_time::ptime BoostHelper::getTime(unsigned int time)
{
  return boost::posix_time::from_time_t(time);
}

boost::posix_time::ptime BoostHelper::getTime(const std::string& time)
{
  return boost::posix_time::time_from_string(time);
}

unsigned int BoostHelper::getTime(boost::posix_time::ptime time)
{
  return boost::posix_time::to_time_t(time);
}

unsigned int BoostHelper::getTime(boost::posix_time::time_duration time)
{
  return time.total_milliseconds();
}

unsigned int BoostHelper::getCurrentTime()
{
  return getTime(getCurrentTimeStamp());
}

boost::posix_time::time_duration BoostHelper::getTimeDuration(const std::string& time)
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
  boost::thread::sleep(boost::get_system_time() + getTimeDuration(seconds));
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
  return toString(getCurrentTimeDuration());
}

boost::posix_time::time_duration BoostHelper::getTimeDuration(float seconds)
{
  long result = std::ceil(seconds * 1000);
  return boost::posix_time::milliseconds(result);
}

boost::posix_time::time_duration BoostHelper::getCurrentTimeDuration()
{
  return getCurrentDateTime().time_of_day();
}

boost::posix_time::time_duration BoostHelper::getCurrentTimeStamp()
{
  boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));
  return (boost::posix_time::microsec_clock::local_time() - epoch);
}

boost::posix_time::ptime BoostHelper::getCurrentDateTime()
{
  return boost::get_system_time() + boost::posix_time::hours(8);
}

std::string BoostHelper::currentTimestamp()
{
  return DevHelper::format("%ld000", getCurrentTimeStamp().total_seconds());
}

std::string BoostHelper::createUUID()
{
  std::string result = boost::uuids::to_string(boost::uuids::random_generator()());
  std::string::iterator begin = std::remove_if(result.begin(), result.end(), [](char ch){ return (ch == '-'); });
  result.erase(begin, result.end());
  return result;
}
