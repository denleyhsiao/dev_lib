#include "dev_lib/comm/comm.h"
#include "dev_lib/dev_helper.h"
#include "dev_lib/log/log_harness.h"

void Comm::write(const data_type& data)
{
  DLOG(INFO) << DevHelper::getType(*this) << " write "<< DevHelper::toHex(data);
  doWrite(data);
}
