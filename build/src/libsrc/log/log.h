#ifndef LOG_H__
#define LOG_H__

#include<iostream>
#include<sstream>
#include "stream.h"


/*!
 * @file Log.h
 * @brief 
 * @author Amitesh Singh <singh.amitesh@gmail.com> 2008
 */

/*!
 * @namespace log
 * @brief namespace log
 * Collection of all the log related classes.
 */
namespace log
{
  /*! 
   * @enum LogSeverity 
   * LS_SENSITIVE == Logging done with the consent of the user
   * LS_VERBOSE ==  Logging done for diagnostic logs
   * LS_INFO == normal logging
   * LS_WARNING == some thing that may warrant investigation 
   * LS_ERROR == some thing that should n't have occurred.
   *
   */
  enum LogSeverity {LS_SENSITIVE,LS_VERBOSE,LS_INFO,LS_WARNING,LS_ERROR};

  /*!
   * @class Log
   * @brief 
   *
   */
  class Log
  {
    LogSeverity mSeverity:3;//!< LogSeverity object; range : 0 -7 
    std::ostringstream mPrintStream;
    std::string mStrSeverity;
    StreamInterface *mStream;//!< StreamInterface pointer

    void setStrSeverity();
    public:
    /*!
     * @brief Param constructor
     *
     */
      Log(const char *file,int line,const char *function,LogSeverity sev);

      /*!
       * @brief destructor
       *
       */
      ~Log();

      /*!
       * @brief anonymous enum
       *
       */
      enum { NO_LOGGING = LS_ERROR + 1 };

      Log& operator<< (int integer);

      Log& operator<< (unsigned int integer);

      Log& operator<< (float);

      Log& operator<< (double);

      Log& operator<< (long);

      Log& operator<< (const long long&);

      Log& operator<< (char ch);

      Log& operator<< (const char *);

      Log& operator<< (const std::string &);

  };
//pretty func is only available in GNUG++
#ifdef __GNUG__
#define LOG(sev) log::Log::Log(__FILE__,__LINE__,__PRETTY_FUNCTION__,log::sev)
#else 
#define LOG(sev) log::Log::Log(__FILE__,__LINE__,__func__,log::sev)
#endif

}

#endif

