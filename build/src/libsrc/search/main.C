#include "PrefixSearch.h"
#include "PrefixSearch.cc"
using namespace std;
int main()
{
  PrefixSearch::Start();//one time call

  vector<string> vec;
  vec.push_back("recent");
  vec.push_back("recent-help");

  PREFIX_POPULATE(vec); //one time call.
  PrefixSearch::mPrefSearch->print();
  vector<string> text;
  string str = "r";
  PREFIX_GET_ENTRY(str,text);

  cout << "Search result of \"r\"=\n";
  for(int i = 0 ;i < text.size();++i)
  {
    cout << text[i] << endl;
  }

  PrefixSearch::End(); //one time call 
}
