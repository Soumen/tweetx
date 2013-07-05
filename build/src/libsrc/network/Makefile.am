lib_LTLIBRARIES = libSocket.la
libSocket_la_SOURCES = base64.h base64.cc socket.h socket.cc httpcommon.h proxy.h httpclient.h httpclient.cc 
libSocket_la_LDFLAGS = -version-info 0:0:0 -lssl -no-undefined -lcrypto
libSocket_la_LIBADD = ../common/libCommon.la ../log/libLog.la ../error/libError.la ../error/libError.la ../timestamper/libTimeStamper.la
#libSocket_la_CXXFLAGS = -fPIC -shared -I../common -I../log  -I../error -I../timestamper/
DEFAULT_INCLUDES = -I${top_srcdir}

#bin_PROGRAMS = smtp
#smtp_SOURCES = smtpclient.cc
#smtp_LDADD = ./libSocket.la ../common/libCommon.la ../log/libLog.la ../error/libError.la
#smtp_CXXFLAGS =  -I../common -I../log  -I../error -I.


