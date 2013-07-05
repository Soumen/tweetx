#ifndef TWEETX_ERROR_ENUM_H
#define TWEETX_ERROR_ENUM_H
#include <iostream>
#include <map>

enum TweetxError 
{
  TE_DNS_ERROR,
  TE_CONNECT_ERROR,
  TE_SSL_CERT_ERROR,
  TE_SSL_CONNECT_ERROR,
  TE_HTTP_OK = 200,
  TE_HTTP_NOT_MODIFIED = 304,
  TE_HTTP_BAD_REQ = 400,
  TE_HTTP_NOT_AUTH = 401,
  TE_HTTP_FORBIDDEN = 403,
  TE_HTTP_NOT_FOUND = 404,
  TE_HTTP_SERVER_ERROR = 500,
  TE_HTTP_BAD_GATEWAY = 502,
  TE_HTTP_SERVICE_NOT_AVAILABLE = 503,
  //Http proxy errors
  //TODO:
  //TE_HTTP_PROXY_*;
  // wrapper errors
  TE_WE_OK = TE_HTTP_OK,     // everything in wrapper went ok
  TE_PARSE_ERROR = 800,      // threw exception in ticpp
  TE_INVALID_OPTION = 801,   // went through switch to default
  TE_LAST
};

template<class Enum,class Value = const char *>
class ErrorAllocator
{
  std::map<Enum,Value> mErrAlloc;
  public:
  void AddDesc(Enum _en,Value _m)
  {
    mErrAlloc[_en] = _m;
  }
  Value operator[](Enum _e)
  {
    return mErrAlloc[_e];
  }
  int Size()
  {
    return mErrAlloc.size();
  }
};

const char * const GetErrorDesc(TweetxError _ea);


#endif
