#include "dev_lib/comm/comm.h"
#include "dev_lib/dev_helper.h"
#include "dev_lib/log/log.h"

void Comm::write(const data_type& data)
{
  log->debug(DevHelper::format("%s write %s", DevHelper::getType(*this).c_str(), DevHelper::convertToHex(data).c_str()));
  doWrite(data);
}
