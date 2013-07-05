#ifndef __TWEETX_THREAD_H__
#define __TWEETX_THREAD_H__

#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<vector>



namespace Tweetx
{
  template<class T>
    class Thread
    {
      pthread_t mThread;
      bool isRunning;
      //
      // Handler object
      //
      T *mObject;

      //
      // Function Arguments
      //
      void *arg1;
      void *arg2;
      void *arg3;

      //
      // Function pointers
      //
      void (T::*funcPtr0)();
      void (T::*funcPtr1)(void *);
      void (T::*funcPtr2)(void *,void *);
      void (T::*funcPtr3)(void *,void *,void *);

      static void *thread_func(void *input)
      {
        ((Thread<T> *)(input))->run();
        pthread_exit(0);
      }
      void run()
      {
        if(funcPtr0 != 0)
          (mObject->*funcPtr0)();
        if(funcPtr1 != 0)
          (mObject->*funcPtr1)(arg1);
        if(funcPtr2 != 0)
          (mObject->*funcPtr2)(arg1,arg2);
        if(funcPtr3 != 0)
          (mObject->*funcPtr3)(arg1,arg2,arg3);
      }
      void funcPtrZero()
      {
        funcPtr0 = 0;
        funcPtr1 = 0;
        funcPtr2 = 0;
        funcPtr3 = 0;
      }
      public:

      Thread(void (T::*func)(),T *obj)
      {
        funcPtrZero();
        funcPtr0 = func;
        mObject = obj;
      }

      Thread(void (T::*func)(void *),T *obj,void *arg1)
      {
        funcPtrZero();
        funcPtr1 = func;
        mObject = obj;
        this->arg1 = arg1;
      }


      Thread(void (T::*func)(void *,void *),T *obj,void *arg1,void *arg2)
      {
        funcPtrZero();
        funcPtr2 = func;
        mObject = obj;
        this->arg1 = arg1;
        this->arg2 = arg2;
      }

      Thread(void (T::*func)(void *,void *,void *),T *obj,void *arg1,void *arg2,void *arg3)
      {
        funcPtrZero();
        funcPtr3 = func;
        mObject = obj;
        this->arg1 = arg1;
        this->arg2 = arg2;
        this->arg3 = arg3;
      }

      /*
      Thread(T *obj)
      {
        funcPtrZero();
        funcPtr0 = &T::run;
      }
      */
      int Start() 
      {
        std::cerr << "Starting the thread " << pthread_self() << std::endl;
        pthread_create(&mThread,0,thread_func,(void *)this);
      }

      int Wait()
      {
        std::cerr << "Waiting for the thread " << pthread_self() << std::endl;
         pthread_join(mThread,0);
      }

      int Stop()
      {
        std::cerr << "Stopping the thread " << pthread_self() << std::endl;
        pthread_cancel(mThread);
      }
    };




  //TODO:
  // There is a bug in the class
  // valgrind hangs while executing it :P
  template<class T>
    class ThreadManager
    {
      std::vector<Thread<T> *> thread_group;
      public:
      ~ThreadManager()
      {
        for(int i = 0; i < thread_group.size(); ++i)
        {
          delete thread_group[i];
        }
        thread_group.clear();

      }
      void AddTask(void (T::*funcPtr)(),T *obj)
      {
        Thread<T> *thread = new Thread<T>(funcPtr,obj);
        thread_group.push_back(thread);
      }

      void Start()
      {
        for(int i = 0; i < thread_group.size(); ++i)
        {
          thread_group[i]->Start();
        }

      }

      void Wait()
      {
        for(int i = 0; i < thread_group.size(); ++i)
        {
          thread_group[i]->Wait();
        }

      }

      void Stop()
      {
        for(int i = 0; i < thread_group.size(); ++i)
        {
          thread_group[i]->Stop();
        }
      }
    };
}
#endif

