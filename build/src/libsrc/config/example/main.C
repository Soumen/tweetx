#include<iostream>
#include <TweetxConfig.h>


int main()
{
  Config::Start();
  //std::cout << Config::GetParam("HTTP_PROXY") << std::endl;
  std::cout << GetConfig(CP_HTTP_PROXY);
  Config::Delete();
  std::cout << "~main()\n";

  return 0;
}
