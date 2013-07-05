#include "src/libsrc/search/PrefixSearch.h"
#include "src/libsrc/third-party/ticpp/ticpp.h"
#include "src/libsrc/tui/TwitterTUI.h"


//
//
// Load function
//
//
void InitializeTweetx()
{
  //start config 
  Config::Start();

  //hash the command list
  PrefixSearch::Start();

  TimeStamper::Start();

  //
  // Run the spellcheck setup.
  SpellChecker sc("words","words.soundex","words.cache");
  sc.RunSetup();

}
//can you think better name?
void DeinitializeTweetx()
{
  //end config
  Config::Delete();

  PrefixSearch::End();
  TimeStamper::End();
}

int main()
{
  InitializeTweetx();

  LOG(LS_INFO)<<GetConfig(CP_USERNAME) << "|" << GetConfig(CP_PASSWORD);
  Tweeter::TweetxTUI tUI;

  DeinitializeTweetx();
  return 0;
}

