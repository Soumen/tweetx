#include <sys/time.h>
#include <iostream>
#include<iomanip>
#include "src/libsrc/log/log.h"

class TimeStamper
{
  enum {algo1,algo2};
  timeval mStart,mEnd,mLapsed;
  TimeStamper(){}
  public:
  double mSpeed;
  static TimeStamper *&getPtr()
  {
    static TimeStamper *mSingleton = 0;
    return mSingleton;
  }

  static void Start()
  {
    if(getPtr() == 0)
    {
      //std::cerr << "allocating new memory\n";

      getPtr()  = new TimeStamper();
    }

  }
  void StartTime();
  void EndTime(size_t &lBytesRead)
  {
    gettimeofday(&mEnd,0);
    if(mStart.tv_usec > mEnd.tv_usec)
    {
      mEnd.tv_usec += 1000000.0;
      mEnd.tv_sec--;
    }
    mLapsed.tv_sec = mEnd.tv_sec - mStart.tv_sec;
    mLapsed.tv_usec = mEnd.tv_usec - mStart.tv_usec;

    mSpeed = (lBytesRead*1.)/(mLapsed.tv_sec + 1./mLapsed.tv_usec);
    //std::cerr << "Speed = " << std::setw(10);
    //std::cerr << float(mSpeed) << " bytes/seconds" << std::endl;
    LOG(LS_INFO) << "Speed = " << (mSpeed) << " bytes/seconds";
    
  }

   



  static void End()
  {
    delete getPtr();
  }

};
