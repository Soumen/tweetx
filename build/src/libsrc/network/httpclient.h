#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H
#include "socket.h"
#include "proxy.h"
//class ProxyInfo;

namespace Http
{
  class HttpClient
  {
    HttpVersion mHttpVer;
    std::string mAgent;
    SocketAddress mServer;
    ProxyInfo mProxyInfo;
    HttpRequestData mRequest;
    HttpResponseData mResponse;
    //HttpAuthResult mHttpAuthRes;
    ProxyInterface *mProxyIntf;
    std::string mUsername;//!< domain username
    std::string mPasswd;//!< domain passwd
    TweetxError mHttpStatus;

    public:
    HttpClient(SocketAddress &_sa):mHttpVer(HVER_1_1),mServer(_sa),mProxyIntf(0),mHttpStatus(TE_HTTP_OK)
    {
    }
    ~HttpClient()
    {
      if(mProxyIntf != 0)
        delete mProxyIntf;
      LOG(LS_INFO)<<"Httpclient is done";
    }
    void setProxy(const ProxyInfo &_proxy)
    {
      mProxyInfo = _proxy;
    }
    void setUsername(const std::string &_name)
    {
      mUsername = _name;
    }
    void setPassword(const std::string &_passwd)
    {
      mPasswd = _passwd;
    }
    HttpResponseData &getHttpResponse()
    {
      return mResponse;
    }

    void IntializeRequest(HttpMethod,std::string,std::string,bool,std::string = "");
    

    void SetAgent(const std::string &_agent)
    {
      mAgent = _agent;
    }

    SocketResult Start();

  };


}
#endif
