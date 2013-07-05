#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>


enum FileError
{
  FE_DONOTEXIST
};

struct WordOffset
{
  char c;
  unsigned int start;
  unsigned int end;
  WordOffset():start(0),end(0){}
  void print()
  {
    std::cerr << "\nc=" << c;
    std::cerr <<"\nstart = " << start;
    std::cerr <<"\nend = " << end << std::endl;
  }
};

class WordOffset;
class SpellChecker
{
  typedef std::map<char,WordOffset> Dictionary;
  Dictionary soundexDict;

  std::string WordFile,SoundexFile,CacheFile;
  bool isFilePresent(std::string sFileName)
  {
    std::ifstream fin;
    fin.open(sFileName.c_str(),std::ios::in);
    if(!fin.is_open())
    {
      fin.close();
      return false;
    }
    fin.close();
    return true;

  }
  FileError MakeSoundexFile();
  FileError LoadDictFile(std::string &,Dictionary &);
  FileError CreateHashFile();
  public:
  // words ==> dictionary
  // words.soundex  ==> soundex file
  // words.cache ==> cache file
  // These files will be MACROS in future.
  // words file will be distributed with Tweetx pkg
  //
  SpellChecker(std::string word,std::string soundex,std::string cache):WordFile(word),
  SoundexFile(soundex),
  CacheFile(cache)
  {
  }

  void RunSetup()
  {
    if(isFilePresent(SoundexFile) && isFilePresent(CacheFile))
      return;
    MakeSoundexFile();
    LoadDictFile(SoundexFile,soundexDict);
    CreateHashFile();
  }
  bool GetSpellSuggestions(std::string sWord,std::vector<std::string> &sSpell); 
};

//
// Soundex Functions
//
std::string GetSoundexStr(std::string &sWord);
std::string ReplaceSoundexStr(char c);
