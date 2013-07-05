#include "PluginLoader.h"

int main()
{
  std::string command = "logger";
  ProxyLoader test;
  test.loadPlugin(command);

  std::cout<<"size:"<<test.mPluginProxy.size();
  PluginFactory *loading = test.pluginObject(command);

  std::vector<std::string> tArgs;
  tArgs.push_back("yahoo");
  tArgs.push_back("google");
  tArgs.push_back("Microsoft");

  std::cout<<loading->executer(tArgs);
}
