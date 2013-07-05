#include "ConfigEnum.h"

/* Generated Config functions - Refer config file for dtls */ 

const char * const GetConfigParam(ConfigParam cp) 
{
 static const char * const configParamArr[CP_LAST] \
      =  \
      {
       "USERNAME",
       "PASSWORD",
       "HTTP_PROXY",
       "HTTP_PORT",
       "MSMTP_COMMAND",
       "MOBILE_NUMBER",
       "MSMTP_TIMEOUT"
      };

 return configParamArr[cp];
}

