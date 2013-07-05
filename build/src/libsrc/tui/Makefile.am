lib_LTLIBRARIES = libTUI.la
libTUI_la_SOURCES = TwitterTUI.h TwitterTUI.C
libTUI_la_LDFLAGS = -version-info 0:0:0 -no-undefined
libTUI_la_LIBADD = -lncurses ../wrapper/libWrapper.la  ../error/libError.la -lpthread ../spellcheck/libSpellCheck.la ../log/libLog.la ../network/libSocket.la ../search/libPSearch.la ../common/libCommon.la ../config/libConfig.la
DEFAULT_INCLUDES = -I${top_srcdir}
libTUI_la_CXXFLAGS = -fPIC -DPLUGIN_DIR='"${prefix}/lib/plugins"'
