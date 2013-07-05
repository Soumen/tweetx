#ifndef HTTP_H__
#define HTTP_H__

#include<iostream>
#include<map>
#include<sstream>
#include<stdlib.h>
#include "src/libsrc/error/ErrorEnum.h"

//#include "socket.h"
using std::map;

namespace Http
{
  /*
     200 OK: everything went awesome.
     304 Not Modified: there was no new data to return.
     400 Bad Request: your request is invalid, and we'll return an error message that tells you why. This is the status code returned if you've exceeded the rate limit (see below). 
     401 Not Authorized: either you need to provide authentication credentials, or the credentials provided aren't valid.
     403 Forbidden: we understand your request, but are refusing to fulfill it.  An accompanying error message should explain why.
     404 Not Found: either you're requesting an invalid URI or the resource in question doesn't exist (ex: no such user). 
     500 Internal Server Error: we did something wrong.  Please post to the group about it and the Twitter team will investigate.
     502 Bad Gateway: returned if Twitter is down or being upgraded.
     503 Service Unavailable: the Twitter servers are up, but are overloaded with requests.  Try again later.
     P.S. ==> 

*/

  enum HttpStatus
  {
    HS_OK = 200,
    NOT_MODIFIED = 304,
    BAD_REQ = 400,
    NOT_AUTH = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    SERVER_ERROR = 500,
    BAD_GATEWAY = 502, 
    SERVICE_NOT_AVAILABLE = 503
  };

  enum HttpVersion
  {
    HVER_1_0,
    HVER_1_1,
    HVER_LAST
  };

  enum HttpMethod 
  {
    GET,
    POST,
    DELETE,
    HM_LAST
  };

  struct HttpData
  {
    std::map<std::string,std::string> mHeaderMap;

    public:
    std::string mHttpMethodCommand;
    std::string mHostCommand;
    std::string mUserAgentCommand;
    std::string mPostDataCommand;
    std::string mContentLengthCommand;
    std::string mContentTypeCommand;
    std::string mAuthCommand;
    
    typedef std::map<std::string,std::string>::iterator ItrHead;
    HttpData()
    {
      mHttpMethodCommand = "HttpMethod";
      mHostCommand = "Host:";
      mUserAgentCommand = "User-Agent:";
      mPostDataCommand = "PostData";
      mContentTypeCommand = "Content-Type:";
      mContentLengthCommand = "Content-Length:";
      mAuthCommand = "Authorization: Basic";
    }
    virtual ~HttpData()
    {
    }
    void addHeader(const std::string &name,const std::string &value) 
    {
      mHeaderMap[name] = value;
    }



  };

  struct HttpRequestData:public HttpData
  {
    std::string mPath;
    public:
    HttpMethod mMethod;
    HttpRequestData():mMethod(GET)
    {
    }

    std::string str()
    {
      const std::string sNewLine("\r\n");
      const std::string sSpace(" ");
      std::string sReqString;
      sReqString += mHeaderMap[mHttpMethodCommand] + sNewLine;
      sReqString += mHostCommand + sSpace + mHeaderMap[mHostCommand] + sNewLine;
      sReqString += mUserAgentCommand + sSpace + mHeaderMap[mUserAgentCommand] + sNewLine;

      sReqString += mAuthCommand + sSpace + mHeaderMap[mAuthCommand] + sNewLine;
      if(mMethod == POST)
      {
        sReqString += mContentLengthCommand + sSpace + mHeaderMap[mContentLengthCommand] + sNewLine;
        sReqString += mContentTypeCommand + sSpace + mHeaderMap[mContentTypeCommand] + sNewLine;
        sReqString += sNewLine;

        sReqString += mHeaderMap[mPostDataCommand] +  sNewLine;
      }
      else
        sReqString += sNewLine;
      //std::cout << "sReqString = " << sReqString << std::endl;

      return sReqString;

    }
  };
  
  struct HttpResponseData:public HttpData
  {
    TweetxError mStatus;
    std::string mData;//!< Http data excluding HttpHeader
    void parseHttpOutput(const std::string &_output)
    {
      mStatus = TE_HTTP_SERVICE_NOT_AVAILABLE;
      std::string sStatusCode;
      std::string sTemp;
      //find the first line
      size_t posStatus = _output.find("Status:");
      
      if(posStatus != std::string::npos)
      {
        //std::cout << "posStatus " << posStatus << std::endl;
        sTemp = _output.substr(posStatus,_output.size() - posStatus);
        std::string sLine = sTemp.substr(0,sTemp.find("\r\n"));
        //std::cout << "sLine = " << sLine << std::endl;
        //std::cout << sLine.find(" ",8);
        std::string sStatusCode = sLine.substr(8,sLine.find(" ",8) - 8);
        //std::cout << "Status Code = " << sStatusCode << std::endl;
        mStatus = TweetxError(atoi(sStatusCode.c_str()));
        //std::cout << "mStaus = " << mStatus << std::endl ;
      }
      size_t httpHeadEndPos = _output.find("\r\n\r\n");
      if(httpHeadEndPos != std::string::npos)
        mData = _output.substr(httpHeadEndPos + 4,_output.size() - httpHeadEndPos);
    }
    void printHttpOutput()
    {
      //std::cout << "Data = " << mData << std::endl;
    }
  };


}

#endif

