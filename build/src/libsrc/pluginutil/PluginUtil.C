#include "PluginUtil.h"
extern "C"
{

  void *gCreateWrapperInstance()
  {
    //std::cout<<"Blah i am in";
    Wrapper *newWrapperInstance = new Wrapper();
    //int *newWrapperInstance = new int();
    //*newWrapperInstance = 10;
    //std::cerr<<"ADDRESS:"<<newWrapperInstance<<std::endl;
    return (void*)newWrapperInstance;
  }

  void *gDestroyWrapperInstance(void* pOldInstance)
  {
    if(pOldInstance!=NULL)
    {
      Wrapper *oldWrapperInstance;
      oldWrapperInstance = (Wrapper*)(pOldInstance);
      delete(oldWrapperInstance);
      pOldInstance = oldWrapperInstance;
    }
    return pOldInstance;
  }
}

