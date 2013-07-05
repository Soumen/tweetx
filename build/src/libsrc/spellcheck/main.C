#include "spellcheck.h"


int main(int argc,char **argv)
{
  if(argc != 2)
  {
    std::cerr << argv[0] << " <word>\n";
    return -1;
  }
  SpellChecker sc("words","words.soundex","words.cache");
  sc.RunSetup();

  std::vector<std::string> vec;
  std::string sWord(argv[1]);
  sc.GetSpellSuggestions(sWord,vec);
  for(int i = 0;i < vec.size();++i)
    std::cerr << vec[i] << std::endl;
  return 0;
}


