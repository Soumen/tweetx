#bin_PROGRAMS = sms
#sms_SOURCES = sendsms.C
#sms_LDADD = ../../config/libConfig.la
#sms_CXXFLAGS = -I../../config -I../../common -I../../error -I../../log -ggdb

lib_pluginsdir=${prefix}/lib/plugins
lib_plugins_LTLIBRARIES = libPluginSendSms.la
libPluginSendSms_la_SOURCES = PluginSendSms.cc
libPluginSendSms_la_LDFLAGS = -version-info 0:0:0  -rdynamic -shared -no-undefined
libPluginSendSms_la_LIBADD = ../../pluginutil/libPluginUtil.la ../../wrapper/libWrapper.la ../../log/libLog.la ../../config/libConfig.la ../../network/libSocket.la
libPluginSendSms_la_CXXFLAGS = -fPIC -shared
DEFAULT_INCLUDES = -I${top_srcdir}
