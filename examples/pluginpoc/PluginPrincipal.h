#ifndef __PRINCIPAL_FACTORY__
#define __PRINCIPAL_FACTORY__
#include <iostream>
class PrincipalFactory
{
  public:
    virtual std::string getStatus()=0;
};
#endif
