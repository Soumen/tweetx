#include "httpclient.h"
#include "base64.h"

namespace Http
{
  std::string &GetMethod(HttpMethod _method)
  {
    static std::string sHttpMethod[HM_LAST] = {"GET","POST","DELETE"};
    return sHttpMethod[_method];
  }
  std::string &GetHttpVersion(HttpVersion _ver)
  {
    static std::string sHttpVer[HVER_LAST] = {"HTTP/1.0","HTTP/1.1"};
    return sHttpVer[_ver];
  }

  void HttpClient::IntializeRequest(HttpMethod _method,std::string _path,std::string _host,bool isAuthRequired,std::string _postData)
  {
    // build first command 
    // GET /path HttpVersion
    mRequest.mMethod = _method;
    std::string sPath = GetMethod(_method) + " " + _path + " " + GetHttpVersion(mHttpVer);
    mRequest.addHeader(mRequest.mHttpMethodCommand,sPath);


    mRequest.addHeader(mRequest.mHostCommand,_host);
    //call base64 function here
    if(isAuthRequired)
    {
      std::string sUsernamePasswd = mUsername + ":" + mPasswd;
      std::string sEncAuthcode = base64::Base64::encode(sUsernamePasswd);
      mRequest.addHeader(mRequest.mAuthCommand,sEncAuthcode);
    }
    //TODO:
    //pick client name from Makefile or config.h
    mRequest.addHeader(mRequest.mUserAgentCommand,"tweetx/1.0 Linux");
    if(_method == POST)
    {
      //std::string sPostDataLength;
      std::stringstream ss;
      ss << _postData.size();
      mRequest.addHeader(mRequest.mContentLengthCommand,ss.str());
      mRequest.addHeader(mRequest.mContentTypeCommand,"application/x-www-form-urlencoded"); 
      mRequest.addHeader(mRequest.mPostDataCommand,_postData);
    }

  }



  SocketResult HttpClient::Start()
  {
    if(!mProxyInfo.isUseProxy())
    {
      LOG(LS_INFO)<<"Direct connection to twitter";
      //std::cout << "\nNot using Proxy\n";
      NSsocket::Socket sock(mServer);
      if(sock.Connect() == -1)
      {
        mHttpStatus = sock.GetError();
        LOG(LS_ERROR)<<"Failed to connect";
        LOG(LS_ERROR) << std::string(GetErrorDesc(mHttpStatus));
        return SR_ERROR;
      }
      std::string sReqHeader = mRequest.str();

      char *cWriteData = (char *)sReqHeader.c_str();
      //std::cout << "input = " << sReqHeader;
      sock.WriteToSocket(cWriteData,sReqHeader.size());
      char cOutput[50000];
      bzero(cOutput,50000);
      sock.ReadFromSocket(cOutput,sizeof(cOutput));
      sock.Close();
      LOG(LS_INFO) << "output = " << cOutput;
      //std::cout << "Output = " << cOutput << std::endl;
      std::string sOutput(cOutput);
      mResponse.parseHttpOutput(sOutput);
      //mResponse.printHttpOutput();
      return SR_SUCCESS;
    }
    else
    {
      switch(mProxyInfo.mProxyType)
      {
        case PT_HTTP:
          mProxyIntf = new HttpProxy(mProxyInfo,mServer,mHttpStatus);
          break;
        case PT_HTTPS:
          mProxyIntf = new HttpProxy(mProxyInfo,mServer,mHttpStatus);

          break;

      }

      if(mProxyIntf->Connect() == -1)
        return SR_ERROR;
      mProxyIntf->Authenticate();
      std::string sReqHeader = mRequest.str();
      //std::cout << "Domain Request Header =" << sReqHeader << std::endl;
      mProxyIntf->Write((char *)sReqHeader.c_str(),sReqHeader.size());
      //TODO:
      //write a function to print valid error message
      if(mHttpStatus != TE_HTTP_OK)
        return SR_ERROR;
      char cOutput[10000];
      mProxyIntf->Read(cOutput,sizeof(cOutput));
      //std::cout << "Response from Domain Server = " << cOutput << std::endl;
      mProxyIntf->Close();
      std::string sOutput(cOutput);
      mResponse.parseHttpOutput(sOutput);
      //mResponse.printHttpOutput();
      return SR_SUCCESS;
    }
  }


}
