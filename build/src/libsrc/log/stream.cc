#include "stream.h"

namespace log
{

  StreamInterface::StreamInterface(StreamState se):mStreamState(se)
  {
  }

  FileStream::FileStream(StreamState se):StreamInterface(se)
  {
    //Always open
    //if(!mFileWriter.is_open())
      mFileWriter.open(LOG_FILE,std::ios::out|std::ios::app);

  }

  StreamResult FileStream::write(std::ostringstream &oStrStream)
  {
    if(!mFileWriter.is_open())
    {
      return SR_ERROR;
    }
    else
    {
      mStreamState = SS_OPEN;
    }
    mFileWriter << oStrStream.str() << std::endl;
  }

  NullStream::NullStream(StreamState se):StreamInterface(se)
  {
  }


  StreamResult NullStream::write(std::ostringstream &oStrStream)
  {
    //no logging silently :P
    return SR_SUCCESS;
  }


  ConsoleStream::ConsoleStream(StreamState se):StreamInterface(se)
  {
  }

  StreamResult ConsoleStream::write(std::ostringstream &oStrStream)
  {
    std::cerr << oStrStream.str() << std::endl;
    return SR_SUCCESS;
  }



  NetworkStream::NetworkStream(StreamState se):StreamInterface(se)
  {
  }

  //TODO:
  //will implement it later
  StreamResult NetworkStream::write(std::ostringstream &oStrStream)
  {
  }


}
