#ifndef SOCKET_H__
#define SOCKET_H__

#include<iostream>
#include<cstring>
#include<bits/basic_string.h>
// fcntl
#include <unistd.h>
#include <fcntl.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h> //To resolve compilation issue on FreeBSD, sockaddr_in/6 are defined here.

#include<netdb.h>
#include<list>
#include<openssl/ssl.h>
#include<openssl/err.h>
#include "src/libsrc/log/log.h"
#include "src/libsrc/error/ErrorEnum.h"
#include "src/libsrc/timestamper/timestamper.h"




namespace NSsocket
{
  //
  //
  //
  //
  //
  enum SocketResult {SR_SUCCESS,SR_ERROR,SR_EOS};

  //
  //
  //
  //
  //
  enum ConnState { CS_CLOSED,CS_CONNECTING,CS_CONNECTED};
  //
  //
  //
  //
  //
  //
  enum IpVer {IPv4,IPv6};

  enum ConnType{CT_PLAIN,CT_SSLV2,CT_SSLV23,CT_SSLV3,CT_TLSV1};


  struct SocketAddress 
  {
    std::string mIp;//!< list;can be ipv4 or ipv6
    std::string mHost;//!< Internet Address; www.twitter.com
    uint16_t mPort;//!< port
    IpVer mIpVer;//!< Ip Version used by Host
    ConnType mConnType;

    public:
    SocketAddress():mConnType(CT_SSLV3),mHost("")
    {
    }

    bool isHostEmpty()
    {
      return mHost.empty();
    }


  };

  class SocketInterface
  {
    protected:
      int mFD;
      sockaddr_storage mSS;
      sa_family_t mSAFamily;
      int mSASockType;
      int mSAProtocol;
      int mSALength;
    public:
      /*!
       * @brief Returns the address to which socket is bound
       * @return SocketAddress
       */
      //TODO:
      //virtual SocketAddress GetLocalAddress() const = 0;
      //virtual SocketAddress GetRemoteAddress() const = 0;
      virtual ~SocketInterface()
      {
      }
      virtual int Connect() = 0;
      virtual int Close() = 0;
      //TODO:
      //change return type to size_t
      virtual size_t WriteToSocket(void *,size_t) = 0;
      virtual size_t ReadFromSocket(void *,size_t) = 0;
      virtual bool GetAddrInfo() = 0;

  };

  class Socket:public SocketInterface
  {
    SocketAddress &mRefSocketAddr;
    SSL *mSsl;
    SSL_CTX *mCtx;
    TweetxError mError;

    void ShowCertificates()
    {
      X509 *cert;
      char *line;
      cert = SSL_get_peer_certificate(mSsl);
      if(cert == 0)
       std::cerr << "No Certificates\n";
      else 
      {
        //std::cout << "Server Certificates:\n";
        line = X509_NAME_oneline(X509_get_subject_name(cert),0,0);
        //std::cout << "Subject: " << line << "\n";
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert),0,0);
        free(line);
        //std::cout << "Issuer: " << line << "\n";
        X509_free(cert);
      }
    }
    void initializeSockStorage();
    void InitCTX();
    int setNonBlocking()
    {
      int flags;
      if((flags = fcntl(mFD,F_GETFL,0)) < 0 )
      {
        perror("problem with setting non-block");
        flags = 0;
      }
      if((flags = fcntl(mFD,F_SETFL,flags | O_NONBLOCK)) < 0)
      {
        perror("problem witj setting non-block");
      }
    }

    int StartSSL();
    public:
    Socket(SocketAddress &ref):mRefSocketAddr(ref),mError(TE_HTTP_OK)
    {
    }
    ~Socket()
    {
    }
    int Connect();
    int Close();
    size_t WriteToSocket(void *,size_t);
    size_t ReadFromSocket(void *,size_t);
    bool GetAddrInfo();
    TweetxError GetError()
    {
      return mError;
    }

  };



} //namespace ends


#endif

