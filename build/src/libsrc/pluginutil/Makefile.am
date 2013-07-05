lib_LTLIBRARIES = libPluginUtil.la
libPluginUtil_la_SOURCES = PluginUtil.h PluginUtil.C
libPluginUtil_la_LDFLAGS = -version-info 0:0:0 -no-undefined
libPluginUtil_la_LIBADD = -lncurses ../wrapper/libWrapper.la  ../error/libError.la ../network/libSocket.la
libPluginUtil_la_CXXFLAGS = -fPIC
#P.S. only this works at the time of make distcheck
DEFAULT_INCLUDES = -I${top_srcdir}
