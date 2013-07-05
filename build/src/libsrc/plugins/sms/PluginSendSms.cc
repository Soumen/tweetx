#include "src/libsrc/pluginarch/PluginCreator.h"
#include "src/libsrc/config/TweetxConfig.h"
#include <stdlib.h>
#include "src/libsrc/wrapper/wrapper.h"
#include "src/libsrc/log/log.h"


class PluginSendSms:public PluginFactory
{
  std::string mCommand;
  public:
    PluginSendSms(){};
    ~PluginSendSms(){};

    bool sendSms(std::string sEmailId,std::string &sTweetMsg)
    {
      //TODO
      //Check for msmtp command
      //
      // Reading from config file is first priority 
      std::string sCommand;
      if(!mCommand.empty())
        sCommand = mCommand;

        /*
           sCommand = "msmtp -t -C ~/.msmtprc -a gmail";
        */
      sCommand += " " + sEmailId;
      FILE *fd = popen(sCommand.c_str(),"w");
      if(fd == NULL)
        return false;
      fprintf(fd,"rcpt to:");
      fprintf(fd,sEmailId.c_str());
      fprintf(fd,"\n");
      fprintf(fd,"Subject: Tweetx Message\n\n");
      fprintf(fd,sTweetMsg.c_str());
      pclose(fd);
      LOG(LS_INFO) << "Hurray! Mail sent";
    }


    std::string  throwWrapperError(TweetxError err)
    {
      std::string sError = GetErrorDesc(err);
      LOG(LS_ERROR) << sError;
      LOG(LS_ERROR) << "Stopping SendSms plugin";
      return sError;
    }


    std::string executer(std::vector<std::string> &pArgs,void *TUIHandler) 
    {
      LOG(LS_INFO) << "***************SEND SMS STARTED**************";
      std::string strDummyRet;
      mCommand = GetConfig(CP_MSMTP_COMMAND);
      if(mCommand.empty())
      {
        LOG(LS_ERROR) << "config entry for msmpt command is absent";
        return "add MSMTP_COMMAND into tweetxrc";
      }
      std::string sEmailId = GetConfig(CP_MOBILE_NUMBER);//"9177882240@airtelap.com";//GetConfig(CP_MOBILE_NUMBER);
      if(sEmailId.empty())
      {
        LOG(LS_ERROR) << "config entry for mobile number is absent";
        return "add MOBILE_NUMBER into tweetxrc";
      }

      if(sEmailId.empty())
        return "***Mobile number is absent in config file \
                   MOBILE_NUMBER=8098210@verizon.mobile.com \
                   ";

      Wrapper wrapper;
      std::vector<Wrapper::WrapperItem> latestTweet = wrapper.Get(Wrapper::FRIENDS_TIMELINE,"NULL");
      //if(wrapper.Get_Error() != TE_HTTP_OK)

       // continue;
      //  return throwWrapperError(wrapper.Get_Error());
      std::string sLatestId;
      if(latestTweet.size() > 0)
        sLatestId= latestTweet.begin()->id;
      unsigned int iTimeout = 300; // default set to 5 minutes
      std::string sTimeout;
      sTimeout= GetConfig(CP_MSMTP_TIMEOUT);
      if(!sTimeout.empty())
      {
        LOG(LS_INFO) << "Reading TIMEOUT from config file";
        iTimeout = atoi(sTimeout.c_str());
      }

      LOG(LS_INFO) << "TIMEOUT=" << sTimeout;
      LOG(LS_INFO) << "Got first latest id =" << sLatestId;
      std::string sColon(":");
      //std::string sLatestId = (wrapper.Get(Wrapper::FRIENDS_TIMELINE,""))->rbegin()->id;
      while(1)
      {
        if(!mPluginStatus)
        {break;}

        LOG(LS_INFO) << "Going to Sleep ";
        sleep(iTimeout);
        //clear the container
        //wrapper.getContainer().clear();
        LOG(LS_INFO) << "wake up from sleep";
        std::vector<Wrapper::WrapperItem> latestTweets = wrapper.Get(Wrapper::FRIENDS_SINCE_ID,sLatestId);
        if(wrapper.Get_Error() != TE_HTTP_OK && wrapper.Get_Error() != TE_PARSE_ERROR)
          continue;
        //Get the lastet created_at 
        //then pass it into 
        //LOG(LS_INFO) << "New Wrapper List Size = " << latestTweets.size();
        for(std::vector<Wrapper::WrapperItem>::reverse_iterator itr = latestTweets.rbegin();itr != latestTweets.rend(); ++itr)
        {
          //wait  for 2 seconds before sending another mail
          LOG(LS_INFO) << "should wait for 2 seconds";
          sleep(2);
          std::string sMsg;
          sMsg = itr->user_name + sColon;
          sMsg += itr->text; //"hey from sendsms@tweetx";

          if(!sMsg.empty())
            sendSms(sEmailId,sMsg);
          LOG(LS_INFO) << "MESSAGE SENT:" << sMsg;
        }

        //wrapper.getContainer().clear();
        sLatestId = (wrapper.Get(Wrapper::FRIENDS_TIMELINE,"NULL")).begin()->id;
        if(wrapper.Get_Error() != TE_HTTP_OK && wrapper.Get_Error() != TE_PARSE_ERROR)
          continue;
         // return throwWrapperError(wrapper.Get_Error());
        LOG(LS_INFO) << "Got latest id in loop=" << sLatestId;
      }
      return strDummyRet;

    }
};

extern "C"
{
  PluginProperties* _registerPlugin()
  {
    PluginProperties* tRegVar = new PluginProperties();

    tRegVar->mIsBackGroundProcess = true;
    tRegVar->mIsEnabled = true;
    tRegVar->mCommandName = "sendsms";
    tRegVar->mCommandSyntax = "sendsms ON/OFF";
    tRegVar->mLongCommadSyntax = "sendsms ON/OFF";
    tRegVar->mOnMessageUpdation = true;
    tRegVar->mTwitterMsgUpdationReq = false;
    tRegVar->mScreenRefresh = true;
    tRegVar->mRunAtInterval = true;
    tRegVar->mTimeInterval = 0;

    //std::cout<<"Aout to return";
    return tRegVar;
  }

  PluginFactory* _initPluginObject()
  {
    //std::cout<<"Inside initPluginObj"<<std::endl;
    PluginSendSms *pluginObject = new PluginSendSms();
    //std::cerr<<"Plugin-ADDR:"<<pluginObject<<std::endl;
    return pluginObject;
  }

  PluginFactory* _destroyPluginObject()
  {

    return NULL;
    //implement lator.
  }
}
