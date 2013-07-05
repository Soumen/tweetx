#ifndef __CONFIGENUM_H__
#define __CONFIGENUM_H__

/* Genrerated configuration header from config file. */

enum ConfigParam
{
  CP_USERNAME,
  CP_PASSWORD,
  CP_HTTP_PROXY,
  CP_HTTP_PORT,
  CP_MSMTP_COMMAND,
  CP_MOBILE_NUMBER,
  CP_MSMTP_TIMEOUT,
  CP_LAST
};

const char * const GetConfigParam(ConfigParam cp);

#endif
