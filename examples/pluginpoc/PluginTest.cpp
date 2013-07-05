#include <stdlib.h>
#include <iostream>
#include <dlfcn.h>
#include "PluginPrincipal.h"
using namespace std;

int main()
{
  void *dlHandler = dlopen("libSamplePlugin.so", RTLD_NOW);
  if(dlHandler == NULL)
  {
    std::cerr<<dlerror()<<std::endl;
    exit(0);
  }

  std::cout<<"Loaded so"<<std::endl;
  void* samplePlugin = dlsym(dlHandler,"getPluginObj");
  std::cout<<"Loaded function"<<std::endl;
  if(samplePlugin == NULL)
  {
    std::cerr<<dlerror()<<std::endl;
    exit(0);
  }
  PrincipalFactory *pluginObj = ((PrincipalFactory*(*)())(samplePlugin))();
  std::cout<<pluginObj->getStatus();
 // PrincipalFactory *pluginObj = reinterpret_cast<PrincipalFactory *()> (samplePlugin)();
}
