#SUBDIRS = examples
bin_PROGRAMS = tweetx
tweetx_SOURCES = TUI.C
tweetx_LDADD =../libsrc/log/libLog.la ../libsrc/network/libSocket.la ../libsrc/config/libConfig.la ../libsrc/tui/libTUI.la  ../libsrc/search/libPSearch.la -lpthread ../libsrc/spellcheck/libSpellCheck.la ../libsrc/common/libCommon.la ../libsrc/error/libError.la ../libsrc/wrapper/libWrapper.la ../libsrc/timestamper/libTimeStamper.la ../libsrc/pluginutil/libPluginUtil.la
tweetx_LDFLAGS = -R ${libdir}
tweetx_CXXFLAGS = -DPLUGIN_DIR='"${prefix}/lib/plugins"' 
DEFAULT_INCLUDES = -I${top_srcdir}
