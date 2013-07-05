#include "spellcheck.h"

//
// run this func when dict file changed 
//
FileError SpellChecker::MakeSoundexFile()
{
  std::ifstream fin;
  std::fstream fout;
  fin.open(WordFile.c_str(),std::ios::in);
  fout.open(SoundexFile.c_str(),std::ios::out);
  if(!fin.is_open() || !fout.is_open())
  {
    return FE_DONOTEXIST;
  }
  std::string sLine,sSoundex;
  while(!fin.eof())
  {
    getline(fin,sLine);
    if(sLine.empty())
      continue;
    sSoundex = GetSoundexStr(sLine);
    fout << sSoundex  << ":" <<  sLine << "\n";
  }

}
FileError SpellChecker::LoadDictFile(std::string &sFileName,Dictionary &dictionary)
{
  //get Dict file path based on Distro
  std::ifstream fin;
  fin.open(sFileName.c_str(),std::ios::in);
  if(!fin.is_open())
  {
    return FE_DONOTEXIST;
  }

  unsigned int lLineNo=0;
  char c;
  std::string sLine;
  char oldC = -1;
  
  std::string sSoundex;
  while(!fin.eof())
  {
    getline(fin,sLine,':');
    if(sLine.empty())
      continue;
    ++lLineNo;
    c = sLine.at(0);
  
    if(oldC != c)
    {
      dictionary[c].start=fin.tellg();
      dictionary[c].c = c;
      unsigned long iWordLen = sLine.length();
      dictionary[c].start -= iWordLen;
    }
    if(c == oldC)
    {
      dictionary[c].end = fin.tellg();
    }
    else
    {
      oldC = c;
    }
    
    getline(fin,sLine);

  }
  fin.close();
  //if main distro not found 
  // use tweetx own dict
}

//
// Run this func when LoadDictFile is called
//

FileError SpellChecker::CreateHashFile()
{
  std::fstream fout;
  fout.open(CacheFile.c_str(),std::ios::out | std::ios::binary);
  if(!fout.is_open())
  {
    return FE_DONOTEXIST;
  }

  Dictionary::iterator itr = soundexDict.begin();
  while(itr != soundexDict.end())
  {
    fout.write((char *)&(itr->second),sizeof(WordOffset));
    ++itr;
  }
  fout.close();

}

bool SpellChecker::GetSpellSuggestions(std::string sWord,std::vector<std::string> &spellSuggestions)
{
  std::ifstream fcache;
  fcache.open(CacheFile.c_str(),std::ios::in);
  //optimize it.
  //TODO
  bool isFound = false;
  WordOffset wo;
  while(!fcache.eof())
  {
    //read the first char
    fcache.read((char *)&wo,sizeof(WordOffset));
    if(wo.c == sWord.at(0))
    {
      isFound = true;
      break;
    }
    else
      continue;

  }
  fcache.close();
  //wo.print();
  if(!isFound)
    return false;
  std::string sWordSoundex = GetSoundexStr(sWord);
  std::ifstream fsoundex;
  fsoundex.open(SoundexFile.c_str(),std::ios::in);
  std::string sSoundex,sWordFile;
  fsoundex.seekg(wo.start);
  while(!fsoundex.eof() && fsoundex.tellg() <= wo.end)
  {
    getline(fsoundex,sSoundex,':');
    getline(fsoundex,sWordFile);
    if(sSoundex == sWordSoundex)
    {
      spellSuggestions.push_back(sWordFile);
    }
    else
      continue;
    
  }
  fsoundex.close();
}

std::string GetSoundexStr(std::string &sWord)
{
  std::string sSoundex(1,sWord.at(0));
  for(int i = 1;i<sWord.length();++i)
  {
    std::string str = ReplaceSoundexStr(sWord.at(i));
    //std::cerr << str;
    if(!str.empty())
      sSoundex += str;
  }

  return sSoundex;
}


std::string ReplaceSoundexStr(char c)
{
  //std::string sChar(1,c);
  //a,e,i,o,u,h,w,y == 0 
  //b,f,p,v ==>1
  //c,g,j,k,q,s,x,z ==>2
  //d,t ==>3
  //l =>4
  //m,n =>5
  //r =>6
  switch(c)
  {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'h':
    case 'w':
    case 'y':
      return "0";
    case 'b':
    case 'f':
    case 'p':
    case 'v':
      return "1";
    case 'c':
    case 'g':
    case 'j':
    case 'k':
    case 'q':
    case 's':
    case 'x':
    case 'z':
      return "2";
    case 'd':
    case 't':
      return "3";
    case 'l':
      return "4";
    case 'm':
    case 'n':
      return "5";
    case 'r':
      return "6";
    default:
      return "";
  }

}




