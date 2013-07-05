#ifndef __PLUGINUTIL_H__
#define __PLUGINUTIL_H__
#include "src/libsrc/wrapper/wrapper.h"

extern "C"
{
  void *gCreateWrapperInstance();
  void *gDestroyWrapperInstance(void*);
}

#endif //__PLUGINUTIL_H__
