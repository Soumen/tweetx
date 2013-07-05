#include "log.h"

namespace log
{
  Log::Log(const char *file,int line,const char *function,LogSeverity sev):mSeverity(sev)
  {
    std::string strPipe("|");
    setStrSeverity();
    time_t rawtime;
    time(&rawtime);
    std::string strTime (ctime(&rawtime));
    long lPosNewLine = strTime.find("\n");
    if(lPosNewLine != std::string::npos)
    {
      std::string temp = strTime;
      strTime = temp.substr(0,lPosNewLine);
    }
    mPrintStream << strTime << strPipe << file << strPipe << line << strPipe << function << strPipe << mStrSeverity << strPipe;

#ifdef FILE_LOGGING
    mStream = new FileStream(SS_OPEN);
#elif CONSOLE_LOGGING
    mStream = new ConsoleStream(SS_OPEN);

#elif NETWORK_LOGGING
    mStream = new NetworkStream(SS_OPEN);
#else
    mStream = new NullStream(SS_OPEN);
#endif

  }

  Log::~Log()
  {
    mStream->write(mPrintStream);
    delete mStream;
  }

  void Log::setStrSeverity()
  {
    switch(mSeverity)
    {
      case LS_SENSITIVE:
        mStrSeverity = "SENSITIVE";
        break;

      case LS_VERBOSE:
        mStrSeverity = "VERBOSE";
        break;

      case LS_INFO:
        mStrSeverity = "INFO";
        break;

      case LS_WARNING:
        mStrSeverity = "WARNING";
        break;

      case LS_ERROR:
        mStrSeverity = "ERROR";
        break;

      default:
        mStrSeverity = "INFO";
    }
  }



  Log& Log::operator<< (int integer)
  {
    mPrintStream << integer;
    return *this;
  }
  Log& Log::operator<< (unsigned int integer)
  {
    mPrintStream << integer;
    return *this;
  }

  Log& Log::operator<< (float fl)
  {
    mPrintStream << fl;
    return *this;
  }

  Log& Log::operator<< (double db)
  {
    mPrintStream << db;
    return *this;
  }

  Log& Log::operator<< (long lg)
  {
    mPrintStream << lg;
    return *this;
  }

  Log& Log::operator<< (const long long& lgLg)
  {
    mPrintStream << lgLg;
    return *this;
  }


  Log& Log::operator<< (char ch)
  {
    mPrintStream << ch;
    return *this;
  }

  Log& Log::operator<< (const char *chPtr)
  {
    mPrintStream << chPtr;
    return *this;
  }

  Log& Log::operator<< (const std::string &str)
  {
    mPrintStream << str;
    return *this;
  }
}
