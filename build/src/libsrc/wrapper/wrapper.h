#ifndef WRAPPER_H
#define WRAPPER_H
#define TIXML_USE_TICPP
#include "src/libsrc/third-party/ticpp/ticpp.h"
#include <string>
#include <iostream>
#include "src/libsrc/network/socket.h"
#include "src/libsrc/network/httpclient.h"
#include "src/libsrc/network/proxy.h"
#include <vector>
#include "src/libsrc/config/TweetxConfig.h"
#include "src/libsrc/log/log.h"
#include "src/libsrc/error/ErrorEnum.h"

class Wrapper
{
  public:
    //
    // These can be used by Plugins
    //
  //  NSsocket::SocketAddress sa;
  //  Http::HttpClient *httpclient; //use new here
  //  Http::HttpMethod httpMethod;

    enum { PUBLIC_TIMELINE, FRIENDS_TIMELINE, FRIENDS_SINCE, FRIENDS_SINCE_ID, DIRECT_MESSAGE_GET, DIRECT_MESSAGE_SENT, USER_TIMELINE };
    enum { NEW_STATUS, ADD_FRIEND, DESTROY_FRIEND, DESTROY_STATUS };
    enum { GET, POST };
    Wrapper(){}
    std::string HTTP_Dispatch(int dispatch_type, std::string url, bool auth, const std::string message);
    void Send_Status(const std::string &message);
    void Parse(const std::string &xml);
    void Send(int send, const std::string message);
    void Send_DM(const std::string recipient, const std::string message);
    TweetxError Get_Error();

    // The Get Method is Below The Following Nested Class
    class WrapperItem
    {
      public:
        WrapperItem(){}
        std::string created_at;
        std::string id;
        std::string text;
        std::string source;
        std::string truncated;
        std::string in_reply_to_status_id;
        std::string in_reply_to_user_id;
        std::string favorited;
        std::string user_id;
        std::string user_name;
        std::string user_screen_name;
        std::string user_description;
        std::string user_location;
        std::string user_profile_image_url;
        std::string user_protected;
        std::string user_followers_count;
        virtual ~WrapperItem()
        {
        }
    }; // end of WrapperItem

    std::vector<WrapperItem> &getContainer(){ return container;}
    std::vector<Wrapper::WrapperItem> Get(int get, const std::string page);


    virtual ~Wrapper()
    {
    //  delete httpclient;
    }
    TweetxError getError()
    {
      return mError;
    }

private:
    std::vector<WrapperItem> container;
    TweetxError mError;

};

#endif // WRAPPER_H
