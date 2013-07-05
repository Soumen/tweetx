lib_pluginsdir=${prefix}/lib/plugins
lib_plugins_LTLIBRARIES = libSamplePlugin.la
libSamplePlugin_la_SOURCES = PluginLogger.cpp
libSamplePlugin_la_LDFLAGS = -version-info 0:0:0 dl -rdynamic -shared -no-undefined
libSamplePlugin_la_LIBADD = ../../pluginutil/libPluginUtil.la ../../wrapper/libWrapper.la ../../network/libSocket.la
libSamplePlugin_la_CXXFLAGS = -fPIC -shared
DEFAULT_INCLUDES = -I${top_srcdir}
