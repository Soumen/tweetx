#define TIXML_USE_TICPP
#include <wrapper.h>

/* PUBLIC_TIMELINE, FRIENDS_TIMELINE, NEW_STATUS, ADD_FRIEND, DESTROY_FRIEND */
/* #FIXME = DIRECT_MESSAGE */
  

int main(int argc, char* argv[])
{
  using namespace std;
  Wrapper wrapper;
  
  /* Vector Populated When Asked for Friends Timeline */
  vector<Wrapper::WrapperItem> myvect;
 
  myvect = wrapper.Get(Wrapper::FRIENDS_TIMELINE, "1");

  /* Send a Status Message */
  wrapper.Send(Wrapper::NEW_STATUS, "Done for the night, SVN Updated :P");
  
  /* Add Friend Example */
  wrapper.Send(Wrapper::ADD_FRIEND, "soumen_banerjee");
  
  /* Accessing the Vector Returned from a Get Method */
  cout << "This is Latest Message(use iterator): " << myvect.front().text << endl;
  
  /* Destroy Friendship Example */
  wrapper.Send(Wrapper::DESTROY_FRIEND, "abstortedminds");
  
  /* Send a Direct Message - not working yet */
  //wrapper.Send(Wrapper::DIRECT_MESSAGE, "Testing direct!", "abstortedminds");

  
  return 0;
}
           
