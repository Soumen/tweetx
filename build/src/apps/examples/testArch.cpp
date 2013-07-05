#include "PluginLoader.h"
#include <wrapper.h>

int main()
{
  Config::Start();
  std::string command = "sendsms";
  ProxyLoader test;
  test.loadPlugin();
  std::vector<std::string> tArgs;
  tArgs.push_back("yahoo");
  tArgs.push_back("google");
  tArgs.push_back("Microsoft");
  std::cout<<test.executeCommand(command,tArgs);
  command = "logging";
  std::cout<<test.executeCommand(command,tArgs);
  test.destroyPluginObj();
  Config::Delete();
}
