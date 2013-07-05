#include "TweetxThread.h"

using namespace std;
class Work
{
  int j;
  public:
  void task1()
  {
    for(int i = 0; i < 10; i++)
    {
      std::cerr << i << " ";
    }

    cerr << __func__ << endl;
  }
  void task2()
  {
    for(int i = 0; i < 10; i++)
    {
      std::cerr << i << " ";
    }
    cerr << __func__ << endl;

  }
  void task3()
  {
    for(int i = 0; i < 10; i++)
    {
      std::cerr << i << " ";
    }
    cerr << __func__ << endl;
  }


};
int main()
{
  Work bb;
  typedef void (Work::*FuncPtr)();
  FuncPtr funcPtr1,funcPtr2,funcPtr3;
  funcPtr1 = &Work::task1;
  funcPtr2 = &Work::task2;
  funcPtr3 = &Work::task3;

  Tweetx::Thread<Work> t1(funcPtr1,&bb);
  t1.Start();
  Tweetx::Thread<Work> t2(funcPtr2,&bb);
  t2.Start();
  Tweetx::Thread<Work> t3(funcPtr3,&bb);
  t3.Start();


  t1.Wait();
  t2.Wait();
  t3.Wait();
  
  /*
  Tweetx::ThreadManager<Work> TM;
  TM.AddTask(funcPtr1,&bb);
  TM.AddTask(funcPtr2,&bb);
  TM.AddTask(funcPtr3,&bb);

  TM.Start();
  */
//  TM.Wait();

 // TM.Stop();


  return 0;
}
