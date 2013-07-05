
//*********************************************************************
//* C_Base64 - a simple base64 encoder and decoder.
//*
//*     Copyright (c) 1999, Bob Withers - bwit@pobox.com
//*
//* This code may be freely used for any purpose, either personal
//* or commercial, provided the authors copyright notice remains
//* intact.
//*********************************************************************

#ifndef BASE64_H__
#define BASE64_H__

#include <string>

namespace base64
{
  class Base64
  {
    public:
      static std::string encode(const std::string & data);
      static std::string decode(const std::string & data);
      static std::string encodeFromArray(const char * data, size_t len);
    private:
      static const std::string Base64Table;
      static const std::string::size_type DecodeTable[];
  };
}


#endif 
