#include "ErrorEnum.h"

const char *const GetErrorDesc(TweetxError _ea)
{
  static ErrorAllocator<TweetxError> errorAlloc;
  if(errorAlloc.Size() == 0)
  {
    errorAlloc.AddDesc(TE_HTTP_OK,"Everything went Awesome");
    errorAlloc.AddDesc(TE_HTTP_NOT_MODIFIED,"Not modified");
    errorAlloc.AddDesc(TE_HTTP_BAD_REQ,"Bad Request");
    errorAlloc.AddDesc(TE_HTTP_NOT_AUTH,"Not Authorised");
    errorAlloc.AddDesc(TE_HTTP_FORBIDDEN,"Forbidden");
    errorAlloc.AddDesc(TE_HTTP_NOT_FOUND,"Not Found");
    errorAlloc.AddDesc(TE_HTTP_SERVER_ERROR,"Server Error");
    errorAlloc.AddDesc(TE_HTTP_BAD_GATEWAY,"Bad Gateway");
    errorAlloc.AddDesc(TE_HTTP_SERVICE_NOT_AVAILABLE,"Service Not Available");
    errorAlloc.AddDesc(TE_PARSE_ERROR,"Parse Error");
    errorAlloc.AddDesc(TE_INVALID_OPTION,"Invalid Argument Supplied to Wrapper");
    errorAlloc.AddDesc(TE_DNS_ERROR,"DNS Server Error");
    errorAlloc.AddDesc(TE_CONNECT_ERROR,"Socket Connect Error");
    errorAlloc.AddDesc(TE_SSL_CERT_ERROR,"SSL Certificates Error");
    errorAlloc.AddDesc(TE_SSL_CONNECT_ERROR,"SSL Connect Error");
  }
  return errorAlloc[_ea];
}
