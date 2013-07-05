lib_LTLIBRARIES = libWrapper.la
#libWrapper_la_SOURCES = wrapper.h wrapper.C ../third-party/ticpp/ticpp.h ../third-party/ticpp/ticpp.cpp ../third-party/ticpp/ticpprc.h ../third-party/ticpp/tinystr.h ../third-party/ticpp/tinystr.cpp ../third-party/ticpp/tinyxml.h ../third-party/ticpp/tinyxml.cpp ../third-party/ticpp/tinyxmlerror.cpp ../third-party/ticpp/tinyxmlparser.cpp 
libWrapper_la_SOURCES = wrapper.h wrapper.C ../third-party/ticpp/ticpp.h ../third-party/ticpp/ticpp.cpp ../third-party/ticpp/ticpprc.h ../third-party/ticpp/tinystr.h ../third-party/ticpp/tinystr.cpp ../third-party/ticpp/tinyxml.h ../third-party/ticpp/tinyxml.cpp ../third-party/ticpp/tinyxmlerror.cpp ../third-party/ticpp/tinyxmlparser.cpp
libWrapper_la_LDFLAGS = -version-info 0:0:0 -no-undefined
libWrapper_la_LIBADD = ../network/libSocket.la ../config/libConfig.la  ../log/libLog.la
libWrapper_la_LIBADD = ../network/libSocket.la ../config/libConfig.la  ../log/libLog.la
libWrapper_la_CXXFLAGS = -DTIXML_USE_TICPP
DEFAULT_INCLUDES = -I${top_srcdir}
#../third-party/ticpp/libTicpp.a #-L../third-party/ticpp -lTicpp
#libWrapper_la_CXXFLAGS = -fPIC -I../network/ -I../third-party/ticpp -I../common -I../log -I../config -I../error -I../timestamper
