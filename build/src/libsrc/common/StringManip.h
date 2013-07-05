#ifndef __STRING_MANIP_H__
#define __STRING_MANIP_H__

#include<sstream>
#include<vector>
#include<cctype> //for isdigit
namespace NSCommon
{
  template<class T>
    std::string ToString(T _t)
    {
      std::stringstream ss;
      ss << _t;
      return ss.str();
    }

  void TrimSpaces(std::string &);

  void Tokenize(const std::string&, std::vector<std::string>&, 
      const std::string&);

  bool IsDigit(std::string);
}










#endif
