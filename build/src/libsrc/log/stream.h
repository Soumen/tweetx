#ifndef STREAM_H__
#define STREAM_H__
#include <iostream>
#include <sstream>
#include<fstream>

//this MACRO is temporarory 
// gonna get file name from config file
#define LOG_FILE "logging.txt"

namespace log
{

  /*!
   * @enum StreamResult 
   * @brief 
   *
   *
   */
  enum StreamResult {SR_ERROR,SR_SUCCESS,SR_BLOCK,SR_EOS};
  /*!
   * @enum StreamState 
   *
   *
   *
   */
  enum StreamState {SS_CLOSED,SS_OPENING,SS_OPEN};

  /*!
   * @enum StreamEvent
   *
   *
   */
  enum StreamEvent {SE_OPEN,SE_READ,SE_WRITE,SE_CLOSE};



  /*!
   * @class StreamInterface 
   * @brief Interface class for Stream
   */
  class StreamInterface
  {
    protected:
      StreamState mStreamState;

    public:
      StreamInterface(StreamState);
      /*!
       * @brief Virtual Destructor
       */
      virtual ~StreamInterface()
      {
      }

      virtual StreamResult write(std::ostringstream &)= 0;

      //virtual StreamState getStreamState() const;

  };

  /*!
   * @class FileStream
   * @brief FileStream class
   * logging into file stream
   */
  class FileStream: public StreamInterface
  {
    std::fstream mFileWriter;//!< fstream writer
    public:
    /*!
     * @brief Param Constructor
     * @param StreamState
     */
    FileStream(StreamState);
    ~FileStream()
    {
      mFileWriter.close();
    }
    /*!
     * @brief function which writes into stream
     * @param ref to std::ostringstream 
     * @return StreamResult
     */
    StreamResult write(std::ostringstream &);
  };


  /*!
   * @class NullStream
   * @brief NullStream class
   * No logging
   */
  class NullStream: public StreamInterface
  {
    public:
      NullStream(StreamState);
      StreamResult write(std::ostringstream &);

  };

  /*!
   * @class ConsoleStream
   * @brief ConsoleStream Class
   * Logging into Console; stdout or stderr
   */
  class ConsoleStream: public StreamInterface
  {
    public:
      ConsoleStream(StreamState);
      ~ConsoleStream(){}
      StreamResult write(std::ostringstream &);

  };

  /*!
   * @class NetworkStream
   * @brief NetworkStream class
   * Logging into Network
   */
  class NetworkStream: public StreamInterface
  {
    public:
      NetworkStream(StreamState);
      StreamResult write(std::ostringstream &);
  };

} //namespace ends



#endif 
