#include "StringManip.h"

namespace NSCommon
{
  void TrimSpaces(std::string &str)
  {
    // Trim Both leading and trailing spaces  
    size_t startpos = str.find_first_not_of(" \t"); // Find the first character position after excluding leading blank spaces  
    size_t endpos = str.find_last_not_of(" \t"); // Find the first character position from reverse af  

    // if all spaces or empty return an empty string  
    if(( std::string::npos == startpos ) || ( std::string::npos == endpos))  
    {  
      str = "";  
    }  
    else  
      str = str.substr( startpos, endpos-startpos+1 );
  }


  /* copied from 
   * http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
   */
  void Tokenize(const std::string& str, std::vector<std::string>& tokens,const std::string& delimiters)
  {
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos)
    {
      tokens.push_back(str.substr(lastPos, pos - lastPos));
      lastPos = str.find_first_not_of(delimiters, pos);
      pos = str.find_first_of(delimiters, lastPos);
    }
  }

  bool IsDigit(std::string str)
  {
    for(int pos = 0;pos < str.size(); ++pos)
    {
      if(!std::isdigit(str.at(pos)))
      {
        return false;
      }
    }
    return true;
  }

}
