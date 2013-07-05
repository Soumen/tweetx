#ifndef __PROXY_H__
#define __PROXY_H__
#include "socket.h"
#include "base64.h"
#include "src/libsrc/common/StringManip.h"
#include "httpcommon.h"
#include "src/libsrc/error/ErrorEnum.h"

using namespace NSsocket;

namespace Http
{

  enum ProxyType 
  {
    PT_NO_PROXY,
    PT_SOCKS_4,
    PT_SOCKS_4a,
    PT_SOCKS_5,
    PT_HTTP,
    PT_HTTPS,

  };
  enum AuthResult
  {
    AR_SUCCESS,
    AR_FAILED
  };
  struct ProxyInfo
  {
    SocketAddress mAddress;//!< proxy server info
    ProxyType mProxyType; //!< proxy type
    std::string mUsername;
    std::string mPasswd;
    ProxyInfo():mProxyType(PT_NO_PROXY),mUsername(""),mPasswd("")
    {
    }

    bool isUseProxy()
    {
      if(mProxyType == PT_NO_PROXY)
        return false;

      return true;
    }

  };

  class ProxyInterface
  {
    protected:

    ProxyInfo &mProxyInfo; //!< proxy server info
    Socket mSocket;//!< socket
    SocketAddress &mServer; //!< domain server
    TweetxError &mHttpStatus;
    

    public:
    ProxyInterface(ProxyInfo &_proxyInfo,SocketAddress &_server,TweetxError &_status):mProxyInfo(_proxyInfo),mSocket(mProxyInfo.mAddress),mServer(_server),mHttpStatus(_status)
    {
    }
    virtual ~ProxyInterface()
    {
    }

    virtual SocketResult Connect() = 0;
    virtual AuthResult Authenticate() =0;
    virtual size_t Write(void *input,size_t lInputLength) = 0;
    virtual size_t Read(void *input,size_t lInputLength) = 0;
    virtual void Close()
    {
      mSocket.Close();
    }

  };

  class HttpProxy:public ProxyInterface
  {
    public:
      HttpProxy(ProxyInfo &_proxyInfo,SocketAddress &_server,TweetxError &_status):ProxyInterface(_proxyInfo,_server,_status)
    {
    }
      SocketResult Connect();
      AuthResult Authenticate();
      size_t Write(void *,size_t);
      size_t Read(void *,size_t);
  };


  SocketResult HttpProxy::Connect()
  {
    mSocket.Connect();
  }
  AuthResult HttpProxy::Authenticate()
  {
    //prepare the Connect Command
    std::string sProxyReqHeader("CONNECT ");
    //TODO:
    //get http version from HttpClient class
    sProxyReqHeader += mServer.mHost + ":" + NSCommon::ToString(mServer.mPort) + " HTTP/1.1\r\n";
    sProxyReqHeader += "Host: " + mServer.mHost +"\r\n";

    //TODO:
    //Test this .... 
    if(!mProxyInfo.mUsername.empty() && !mProxyInfo.mPasswd.empty())
    {
      //do basic Auth with Proxy Server
      std::string sUsernamePasswd = mProxyInfo.mUsername + ":" + mProxyInfo.mPasswd;
      std::string sEncData = base64::Base64::encode(sUsernamePasswd);
      sProxyReqHeader += "Proxy-Authorization: Basic " + sEncData + "\r\n";
    }
    //TODO:
    //Check Proxy-Connection: 
    sProxyReqHeader += "Proxy-Connection: Keep-Alive\r\n\r\n";
    //send request header to proxy server
    mSocket.WriteToSocket((char *)sProxyReqHeader.c_str(),sProxyReqHeader.size());

    //read the server response
    char cServerRsp[39];
    bzero(cServerRsp,sizeof(cServerRsp));
    mSocket.ReadFromSocket(cServerRsp,sizeof(cServerRsp));
    //if status = 200 ;;; everything went awesome else
    //throw error
    //std::cout << "input = " << sProxyReqHeader << std::endl;
    //find the http proxy rsp code
    std::string sProxyStatusCode;  
    std::string sTemp;
    std::string sServerRsp(cServerRsp);
    sTemp = sServerRsp.substr(9,sServerRsp.size() - 9);
    sProxyStatusCode = sTemp.substr(0,sTemp.find(" "));

    //std::cout << "Proxy Server Response = " << cServerRsp << std::endl;
    //std::cout << "Proxy Server status code = " << sProxyStatusCode << std::endl;
    //set the status
    mHttpStatus = TweetxError(atoi(sProxyStatusCode.c_str()));
  }
  size_t HttpProxy::Write(void *input,size_t lInputLength)
  {
    size_t lWriteChars;
    lWriteChars = mSocket.WriteToSocket(input,lInputLength);
    return lWriteChars;
  }
  size_t HttpProxy::Read(void *output,size_t lOutputLength)
  {
    size_t lReadChars;
    lReadChars = mSocket.ReadFromSocket(output,lOutputLength);
    return lReadChars;
  }

}


#endif
