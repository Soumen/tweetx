#ifndef _PLUGIN_LOADER_H_
#define _PLUGIN_LOADER_H_

#include <iostream>
#include <dlfcn.h>
#include <stdlib.h>
#include <map>
#include <list>
#include <dirent.h>
#include <stdio.h>
#include <pthread.h>
#include "PluginCreator.h"
#include <string.h>
#include <unistd.h>
#include <signal.h>

class ProxyLoader
{
  public:
    std::map<std::string,PluginProperties *> mPluginProxy;
    std::map<std::string,pthread_t> mRunningThreads;

    std::string mCurrentCommand;
    std::vector<std::string> mCurrentParam;

    ProxyLoader(){};
    ~ProxyLoader(){};

    void loadPlugin()
    {
      std::string plugindir = PLUGIN_DIR;
      std::string sysComm = "ls -rt1 ";
      sysComm += plugindir;
#ifdef __CYGWIN__
			sysComm += "/*.dll*";
#else
      sysComm += "/*.so";
#endif
      FILE *fPtr = popen(sysComm.c_str(),"r");
      if(fPtr==NULL) return;

      int iMemSize = plugindir.size() + 200;

      std::string pluginPath;
      char *commadRet = new char[iMemSize];

      while(!feof(fPtr))
      {
        memset(commadRet,'\0',iMemSize);
        fscanf(fPtr,"%s",commadRet);
        pluginPath = commadRet;
        if(pluginPath.size()==0)
          break;

        void *dlHandler = dlopen(pluginPath.c_str(), RTLD_NOW);
        if(dlHandler == NULL) { continue; }

        void* tRegisterPlugin = dlsym(dlHandler,"_registerPlugin");
        if(tRegisterPlugin == NULL) { continue; } 

        PluginProperties *tPluginProp = 
          ((PluginProperties*(*)())(tRegisterPlugin))();

        if(tPluginProp!=NULL)
        {
          //Reject plugin if name not found. 
          std::string tCommandName = "/";
          tCommandName += tPluginProp->mCommandName;

          tPluginProp->mPluginLocator = dlHandler;
          mPluginProxy[tCommandName] = tPluginProp;
          tPluginProp->mDerivePluginObject = 
            pluginObject(tCommandName);
          mPluginProxy[tCommandName] = tPluginProp;
        }
      }
      pclose(fPtr);
      delete commadRet;
    }

    PluginFactory* pluginObject(std::string &pCommandName)
    {
      PluginFactory *tPluginObj;
      if(mPluginProxy.find(pCommandName) != mPluginProxy.end())
      {
        void* tInitPlugin = dlsym
          ((mPluginProxy[pCommandName])->mPluginLocator,"_initPluginObject");
        if(tInitPlugin == NULL)
        {
          return NULL;
        }
        tPluginObj =
          ((PluginFactory*(*)())(tInitPlugin))();
      }
      return tPluginObj;
    }

    void destroyPluginObj()
    {
      for(std::map<std::string,pthread_t>::iterator itrThreads=mRunningThreads.begin();
          mRunningThreads.size()>0 && itrThreads!=mRunningThreads.end();
          itrThreads++)
      {
        pthread_kill(itrThreads->second,0);
      }
      mRunningThreads.clear();

      for(std::map<std::string,PluginProperties*>::iterator itrPlugins 
          = mPluginProxy.begin();mPluginProxy.size()>0 
          && itrPlugins!=mPluginProxy.end(); itrPlugins++)
      {
        delete ((itrPlugins->second)->mDerivePluginObject);
        void* dlHandler = (itrPlugins->second)->mPluginLocator;
        delete (itrPlugins->second);
        dlclose(dlHandler);
      }
      mPluginProxy.clear();
    }

    static void* run(void* param)
    {
      ProxyLoader *me = (ProxyLoader*)param;
      std::string pComm = me->mCurrentCommand;
      std::vector<std::string> pArgs = me->mCurrentParam;
      me->mCurrentCommand = "";
      me->mCurrentParam.clear();
      ((me->mPluginProxy[pComm])->mDerivePluginObject->executer(pArgs));
    }

    std::string executeCommand(std::string& pComm,std::vector<std::string> &pArgs)
    {
      if(mPluginProxy.find(pComm)!=mPluginProxy.end())
      {
        if(mPluginProxy[pComm]!=NULL)
        {
          if((mPluginProxy[pComm])->mDerivePluginObject != NULL)
          {
            std::string retVal;
            if((mPluginProxy[pComm])->mIsBackGroundProcess)
            {
              pthread_t thread_t;
              mCurrentCommand = pComm;
              mCurrentParam = pArgs;
              int ret_code = pthread_create(&thread_t,NULL,run,(void*)this);
              mRunningThreads[mCurrentCommand]=thread_t;
            }
            else
            {
              retVal = ((mPluginProxy[pComm])->mDerivePluginObject->executer(pArgs));
            }
            return retVal;
          }
        }
      }
    }
};

#endif
