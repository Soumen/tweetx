#include "socket.h"

//TODO:
//use LOG_MSG

namespace NSsocket
{
  bool Socket::GetAddrInfo()
  {
    bzero(&(this->mSS),sizeof(this->mSS));
    if(mRefSocketAddr.isHostEmpty())
    {
      return false;
    }
    struct addrinfo hints,*result,*ptr;
    int error;
    bzero(&hints,sizeof(hints));
    hints.ai_family = AF_UNSPEC;//Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // only using TCP
    hints.ai_flags = 0; 
    hints.ai_protocol = 0; //Any protocol

    error = getaddrinfo(mRefSocketAddr.mHost.c_str(),NULL,&hints,&result);
    if(error != 0)
    {
      //std::cerr << gai_strerror(error);
      //TODO:
      //set correct error message here
      mError = TE_DNS_ERROR;
      LOG(LS_ERROR) << gai_strerror(error);
      return false;
    }

    char chIpStr[INET6_ADDRSTRLEN];
    ptr = result;

    while(ptr)
    {
      void *ipAddr;

      switch(ptr->ai_family)
      {
        case AF_INET:
        {
          sockaddr_in *ipv4 = (sockaddr_in *)(ptr->ai_addr);
          
          ipAddr = &(ipv4->sin_addr);
          mRefSocketAddr.mIpVer = IPv4;
        }
        break;
        case AF_INET6:
        {
          sockaddr_in6 *ipv6 = (sockaddr_in6 *)(ptr->ai_addr);
          ipAddr = &(ipv6->sin6_addr);
          mRefSocketAddr.mIpVer = IPv6;
        }
        break;

        default:
        mError = TE_DNS_ERROR;
        LOG(LS_ERROR)<<"Unknown Family type";
        return false;
      }
      mSS.ss_family = mSAFamily = ptr->ai_family;
      mSASockType = ptr->ai_socktype;
      mSAProtocol = ptr->ai_protocol;
      mSALength = ptr->ai_addrlen;

      inet_ntop(ptr->ai_family,ipAddr,chIpStr,sizeof(chIpStr));
      if(ptr->ai_family == AF_INET)
      {
        
        inet_pton(ptr->ai_family,chIpStr,&(((sockaddr_in *)&mSS)->sin_addr));
        ((sockaddr_in *)&mSS)->sin_port = htons(mRefSocketAddr.mPort);
      }
      else 
      {
        inet_pton(ptr->ai_family,chIpStr,&(((sockaddr_in6 *)&mSS)->sin6_addr));
        ((sockaddr_in6 *)&mSS)->sin6_port = htons(mRefSocketAddr.mPort);
      }

      //std::cout << chIpStr << std::endl;
      mRefSocketAddr.mIp = chIpStr;
      ptr = ptr->ai_next;
    }
    freeaddrinfo(result);

    return true;
  }

  void Socket::initializeSockStorage()
  {
    bzero(&mSS,sizeof(mSS));
    mSAFamily = AF_INET;
    mSASockType = SOCK_STREAM;
    mSAProtocol = 0;
    mSS.ss_family = AF_INET;
    inet_pton(AF_INET,mRefSocketAddr.mIp.c_str(),&(((sockaddr_in *)&mSS)->sin_addr));
    ((sockaddr_in *)&mSS)->sin_port = htons(mRefSocketAddr.mPort);
  }


  int Socket::Connect()
  {
    //initialize Remote Address
    if(!mRefSocketAddr.isHostEmpty())
      GetAddrInfo();
    else
      initializeSockStorage();
    mFD = ::socket(mSAFamily,mSASockType,mSAProtocol);
    int error;
    error = ::connect(mFD,(struct sockaddr *)&(mSS),mSALength);
    if(error == -1)
    {
      //perror("problem while connecting ..");
      //log it into our stream as well
      mError = TE_CONNECT_ERROR;
      LOG(LS_ERROR)<<"problem while connecting ..";
      return -1;
    }

    if(mRefSocketAddr.mConnType != CT_PLAIN)
      StartSSL();
    //set the socket into non blocking mode
    //setNonBlocking();
  }

  int Socket::Close()
  {
    if(mRefSocketAddr.mConnType != CT_PLAIN)
    {
      SSL_shutdown(mSsl);
      SSL_free(mSsl);
    }
    close(mFD);
    if(mRefSocketAddr.mConnType != CT_PLAIN)
      SSL_CTX_free(mCtx);
  }


  size_t Socket::ReadFromSocket(void *output,size_t lOutputLength)
  {
    //bzero(output,lOutputLength);
    struct timeval waitd;
    fd_set readFlags;
    size_t lReadChars = lOutputLength;
    int err ;
    size_t n = 0;
    char *ptr = (char *)output;
    size_t lBytesRead = 0;
    int i =0;
    while(lReadChars > 0)
    {
      //TimeStamper::getPtr()->StartTime();
      //waitd.tv_sec=1;
      //waitd.tv_usec = 0;
      //FD_ZERO(&readFlags);
      //FD_SET(mFD,&readFlags);

      //err = select(mFD + 1,&readFlags,0,0,&waitd);
      //if(err <= 0)
      //  break;
     // if(FD_ISSET(mFD,&readFlags))
     // {
      //  FD_CLR(mFD,&readFlags);
        if(mRefSocketAddr.mConnType == CT_PLAIN)
          n = read(mFD,ptr,lReadChars);
        else 
          n = SSL_read(mSsl,ptr,lReadChars);
        //if(n == 0)
         // TimeStamper::getPtr()->mSpeed = 0;
        //TimeStamper::getPtr()->EndTime(n);
        if (n <= 0)
          break;
        //LOG(LS_INFO) << "n = " << n;
        ptr += n;

        lBytesRead += n;
        lReadChars -= n;
     // }
    }
    //LOG(LS_INFO) << "Total read data = " << lBytesRead;
    return lBytesRead;
    }

  size_t Socket::WriteToSocket(void *input,size_t lInputLength)
  {
    size_t lWriteChars = lInputLength;
    size_t n = 0;
    char *ptr = (char *)input;
    size_t lBytesWrite = 0;
    while(lWriteChars > 0)
    {
      if(mRefSocketAddr.mConnType == CT_PLAIN)
        n = write(mFD,ptr,lWriteChars);
      else 
        n = SSL_write(mSsl,ptr,lWriteChars);

      if( n <= 0)
        break;
      ptr += n;
      lBytesWrite += n;
      lWriteChars -= n;
    }
    return lBytesWrite;
  }

  void Socket::InitCTX()
  {
    SSL_METHOD *method;
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    SSL_library_init();
    switch(mRefSocketAddr.mConnType)
    {
      case CT_SSLV2:
        method = const_cast<SSL_METHOD*>(SSLv2_client_method());
        break;
      case CT_SSLV23:
        method = const_cast<SSL_METHOD*>(SSLv23_client_method());
        break;
     case CT_SSLV3:
        method = const_cast<SSL_METHOD*>(SSLv23_client_method());
        break;
     case CT_TLSV1:
        method = const_cast<SSL_METHOD*>(TLSv1_client_method());
        break;
    }

    mCtx = SSL_CTX_new(method);
    if(mCtx == 0)
    {
      ERR_print_errors_fp(stderr);
      mError = TE_SSL_CERT_ERROR;
      abort();
    }
  }

  int Socket::StartSSL()
  {
    InitCTX();
    mSsl = SSL_new(mCtx);
    SSL_set_fd(mSsl,mFD);
    int connRes = SSL_connect(mSsl);
    if(connRes == -1)
    {
      ERR_print_errors_fp(stderr);
      mError = TE_SSL_CONNECT_ERROR;
    }
    else
      ShowCertificates();
    return connRes;

  }
}

