#ifndef PREFIX_SEARCH_H
#define PREFIX_SEARCH_H
#include<iostream>
#include<vector>
#include<map>
#include<set>

#define PREFIX_POPULATE(vec) PrefixSearch::mPrefSearch->populateHashTable(vec)

#define PREFIX_GET_ENTRY(prefix,text) PrefixSearch::mPrefSearch->getEntry(prefix,text)

#define PREFIX_FRIEND_POPULATE(vec) PrefixSearch::mFriendPrefSearch->populateHashTable(vec)

#define PREFIX_FRIEND_GET_ENTRY(prefix,text) PrefixSearch::mFriendPrefSearch->getEntry(prefix,text)



class PrefixSearch
{
  std::multimap<std::string,std::string *> hashTable;
  std::set<std::string *> cache;
  void populateMap(std::string);
  PrefixSearch()
  {
  }
  public:
  void print();
  void getEntry(const std::string prefix,std::vector<std::string> &text);
  void populateHashTable(std::vector<std::string> &);
  static PrefixSearch *mPrefSearch;
  static PrefixSearch *mFriendPrefSearch;
  static void Start()
  {
    if(mPrefSearch == 0)
      mPrefSearch = new PrefixSearch();
    if(mFriendPrefSearch == 0)
      mFriendPrefSearch = new PrefixSearch();
  }

  static void End()
  {
    delete mPrefSearch;
    delete mFriendPrefSearch;
  }
  ~PrefixSearch()
  {
    for(std::set<std::string *>::iterator itr = cache.begin();itr != cache.end();++itr)
    {
      delete *itr;
    }
  }
};
//PrefixSearch  *PrefixSearch::mPrefSearch = 0;
//PrefixSearch  *PrefixSearch::mFriendPrefSearch = 0;

#endif

