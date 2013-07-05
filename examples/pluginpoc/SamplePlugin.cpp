#include "PluginPrincipal.h"

extern "C"
{

  class PluginTestDer:public PrincipalFactory
  {
    std::string getStatus()
    {
      return "i am happy";
    }
  };

  PrincipalFactory* getPluginObj()
  {
    PrincipalFactory* testVal = new PluginTestDer();
    return testVal;
  }

}
