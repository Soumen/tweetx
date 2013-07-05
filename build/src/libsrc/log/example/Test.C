//how to compile
//g++ -o Test Test.C ../libLog.so

#include<iostream>

using namespace std;
#include "../log.h"
class A
{
  public:
    void print()
    {
      LOG(LS_INFO)<<'A';
    }
};


int main()
{
  LOG(LS_ERROR)<<10<<1000;
  LOG(LS_INFO)<<100;
  LOG(LS_INFO)<<"Hello amitesh";
  string str = "Tweetx::Hello";
  LOG(LS_ERROR)<<str<<5.4;
  long long lgLg = 100;
  LOG(LS_ERROR)<<lgLg;

  A aObj;
  aObj.print();
  return 0;
}
