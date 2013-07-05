SUBDIRS = wrapper

bin_PROGRAMS = Logger
Logger_SOURCES = testArch.cpp
Logger_LDADD = ../../libsrc/wrapper/libWrapper.la ../../libsrc/error/libError.la ../../libsrc/third-party/ticpp/libTicpp.a -lpthread
Logger_CXXFLAGS = -I../../libsrc/pluginarch -I../../libsrc/wrapper -I../../libsrc/network -I../../libsrc/error -I../../libsrc/third-party/ticpp -I../../libsrc/log -I../../libsrc/config -I../../libsrc/common -ggdb -DPLUGIN_DIR='"${prefix}/lib/plugins"' -I../../libsrc/timestamper

