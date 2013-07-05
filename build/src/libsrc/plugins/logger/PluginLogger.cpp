#include "src/libsrc/pluginarch/PluginCreator.h"
#include "src/libsrc/pluginutil/PluginUtil.h"
#include "src/libsrc/wrapper/wrapper.h"
#include <unistd.h>

extern "C"
{

  class PlugLogging:public PluginFactory
  {
    public:
      PlugLogging(){};
      ~PlugLogging(){};

      std::string executer(std::vector<std::string> &pArgs,void * pTUIHandler) 
      {
        //std::cerr<<"Got in will sleep for 1 mins...sleeping\n";
        sleep(60);
        Wrapper *ptrWrapper = (Wrapper*)gCreateWrapperInstance();
        std::vector<Wrapper::WrapperItem> myvect;

        myvect = ptrWrapper->Get(Wrapper::FRIENDS_TIMELINE, "NULL");

        for(std::vector<Wrapper::WrapperItem>::iterator itr=myvect.begin();
            myvect.size()>0 && itr!=myvect.end(); itr++)
        {
          //std::cout<<"Tweet: ["<<itr->text<<"]\n";
        }

        std::string tRetVal;
        for(std::vector<std::string>::iterator itr = pArgs.begin();
            pArgs.size()>0 && itr!=pArgs.end(); itr++)
        {
          tRetVal+=" ";
          tRetVal+=*itr;
        }
        delete ptrWrapper;
        return tRetVal;
      }
  };

  PluginProperties* _registerPlugin()
  {
    PluginProperties* tRegVar = new PluginProperties();

    tRegVar->mIsBackGroundProcess = false;
    tRegVar->mIsEnabled = true;
    tRegVar->mCommandName = "logging";
    tRegVar->mCommandSyntax = "logging ON/OFF";
    tRegVar->mLongCommadSyntax = "logging ON/OFF";
    tRegVar->mOnMessageUpdation = true;
    tRegVar->mTwitterMsgUpdationReq = false;
    tRegVar->mScreenRefresh = true;
    tRegVar->mRunAtInterval = false;
    tRegVar->mTimeInterval = 0;

    //std::cout<<"Aout to return";
    return tRegVar;
  }

  PluginFactory* _initPluginObject()
  {
    //std::cout<<"Inside initPluginObj"<<std::endl;
    PlugLogging *pluginObject = new PlugLogging();
    return pluginObject;
  }

  PluginFactory* _destroyPluginObject()
  {
    return NULL;
    //implement lator.
  }

}
