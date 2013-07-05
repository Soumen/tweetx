#include<iostream>
using namespace std;
#include "../socket.h"
#include "../httpclient.h"
#include "../proxy.h"
using namespace NSsocket;
//#define USE_HTTP_PROXY
int main(int argc,char **argv)
{
  //socket details for domain server 
  SocketAddress sa;
  //if u r using proxy
  Http::ProxyInfo proxy;
  sa.mHost = "www.twitter.com";
  //use sa.mIp if u r using IP
  //
  sa.mPort = 443;
  sa.mConnType = CT_TLSV1; // if !ssl ==> CT_PLAIN
#ifdef USE_HTTP_PROXY

  //define proxy details
  proxy.mAddress.mHost = "abs.ishidden.net";
  proxy.mAddress.mPort = 8080;
  proxy.mAddress.mConnType = CT_PLAIN;
  proxy.mProxyType = Http::PT_HTTP; //set proxy type ; currently only supporting PT_HTTP and PT_HTTPS
  sa.mPort = 80;
  sa.mConnType = proxy.mAddress.mConnType; //remember ; connType of proxy and domain are same.

#endif
#ifdef USE_HTTPS_PROXY
  //define proxy details for https proxy
  proxy.mAddress.mIp = "222.41.192.146";
  proxy.mAddress.mPort = 808;
  proxy.mAddress.mConnType = CT_SSLV2;
  proxy.mProxyType = Http::PT_HTTPS;
  sa.mPort = 443;
  sa.mConnType = proxy.mAddress.mConnType;

#endif


  //Socket mySocket(sa);

  //define your HttpClient
  // arg--> Socket to Domain Server
  Http::HttpClient httpclient(sa); 
  // your HttpMethod
  // GET/POST/DELETE
  Http::HttpMethod httpMethod;
  httpMethod = Http::POST;
  httpclient.setUsername("tweetxdev");
  httpclient.setPassword("amitesh");
#ifdef USE_HTTP_PROXY
  //set the proxy if you are using Proxy
  httpclient.setProxy(proxy);
#endif
#ifdef USE_HTTPS_PROXY
  httpclient.setProxy(proxy);
#endif


  //intialize HttpRequest Header
  // 1st Arg --> HttpMethod
  // 2ndArg ==> Path
  // 3arg ==> Domain Server
  // 4th Arg ==> isAuth Required
  // 5th Arg ==> post message in case of POST
  // see httpclient.cc/.h files for more details
  httpclient.IntializeRequest(httpMethod,"/statuses/update.json","www.twitter.com",true,"status= added non-block support :)");
  
  //start the connection
  if(httpclient.Start() == SR_ERROR)
  {
    std::cerr << "\n Some problem with proxy server Aborting the connection\n";
  }
  //mySocket.Connect();
  //string s = "GET /statuses/public_timeline.xml HTTP/1.0\r\n\r\n";
  //string s = "GET /index.html HTTP/1.1\r\n\r\n";
  //cout << "Wrting to socket\n";
  //char *df = (char *)s.c_str();
  //mySocket.WriteToSocket(df,s.size());
  //char output[100000];
  //mySocket.ReadFromSocket(output,sizeof(output));

  //get the HttpRsp
  Http::HttpResponseData &responseData = httpclient.getHttpResponse();
  //you will not get any data in case of Post HttpMethod
  //you can check for HttpStatus @HttpResponseData
  // responseData.mStatus ??? if its OK, everything went cool. :)
  // look @HttpStatus @httpcommon.h
  // now populating responseData.mStatus 
  // if responseData.mStatus == OK ==> everthing went fine,
  std::cout << "Data from HttpResponseData= " << responseData.mData << std::endl;
  std::cout << "Http Status == " << responseData.mStatus << std::endl;

  return 0;
}
