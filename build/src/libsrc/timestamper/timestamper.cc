#include "timestamper.h"

void TimeStamper::StartTime()
{
  gettimeofday(&mStart,0);
}
#ifdef MAKE_BINARY
int main()
{
  size_t n = 1000;
  TimeStamper::Start();
  TimeStamper::getPtr()->StartTime();
  TimeStamper::getPtr()->EndTime(n);




  TimeStamper::End();

  return 0;
}
#endif
