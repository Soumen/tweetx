#include "PrefixSearch.h"

PrefixSearch *PrefixSearch::mPrefSearch = 0;
PrefixSearch *PrefixSearch::mFriendPrefSearch = 0;

void PrefixSearch::populateMap(std::string command)
{
  bool isFound = false;
  for(std::set<std::string *>::iterator itr = cache.begin();itr != cache.end();++itr)
  {
    //if(cache.find(&command) == cache.end())
    if(*(*itr) == command)
    {
      isFound = true;
      break;
    }
  }
  if(!isFound)
  {
    std::string *ptrCommand = new std::string(command);
    cache.insert(ptrCommand);
    for(int i = 1;i < command.size();++i)
    {
      hashTable.insert(std::pair<std::string,std::string *>(command.substr(0,i),ptrCommand));
    }

  }

}

void PrefixSearch::print()
{
  //printing hash table
  for(std::multimap<std::string,std::string *>::iterator itr = hashTable.begin();itr != hashTable.end(); ++itr)
  {
    std::cout << itr->first << "=" << *itr->second << std::endl;
  }
}

void PrefixSearch::populateHashTable(std::vector<std::string> &vecCommands)
{

  for(unsigned int commandNo = 0;commandNo <vecCommands.size();++commandNo)
  {

    populateMap(vecCommands[commandNo]);

  }

}


void PrefixSearch::getEntry(const std::string prefix,std::vector<std::string> &text)
{
  typedef std::multimap<std::string,std::string *>::iterator ItrMap;
  std::pair<ItrMap,ItrMap> commandP;
  commandP = hashTable.equal_range(prefix);
  for(ItrMap itr = commandP.first;itr != commandP.second;++itr)
  {
    text.push_back(*itr->second);
  }

}
